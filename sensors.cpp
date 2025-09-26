#include "sensors.h"
#include "pinout.h"

// Einstellungen für Gasgriff-Kalibrierung und -Verhalten
const int GAS_ADC_MIN = 200;    // Kalibrierter Minimalwert (anpassen!)
const int GAS_ADC_MAX = 3800;   // Kalibrierter Maximalwert (anpassen!)
const float GAS_DEADZONE_LOW  = 0.05f;  // 5% Totweg unten
const float GAS_DEADZONE_HIGH = 0.02f;  // 2% Totweg oben
const float GAS_SMOOTH_ALPHA  = 0.15f;  // Glättungsfaktor (0.0 - 1.0), kleiner = mehr Glättung

static float smoothedThrottle = 0.0f;   // Persistenter Wert für EMA (Signalglättung)
volatile uint32_t pasTickCount = 0;     // Für PAS-Impulse (Interrupt)

// PAS-Interrupt-Handler
void IRAM_ATTR pasInterruptHandler() {
    pasTickCount++;
}

float processThrottle(uint16_t raw) {
    // 1. Mapping auf 0..1 (normiert)
    float mapped = (float)(raw - GAS_ADC_MIN) / (float)(GAS_ADC_MAX - GAS_ADC_MIN);
    mapped = constrain(mapped, 0.0f, 1.0f);

    // 2. Totweg unten
    if (mapped < GAS_DEADZONE_LOW) mapped = 0.0f;
    // 3. Totweg oben
    if (mapped > (1.0f - GAS_DEADZONE_HIGH)) mapped = 1.0f;

    // 4. Signalglättung (Exponentieller gleitender Mittelwert)
    smoothedThrottle = (GAS_SMOOTH_ALPHA * mapped) + (1.0f - GAS_SMOOTH_ALPHA) * smoothedThrottle;
    return smoothedThrottle;
}

void Sensors::begin() {
    // Analoge Sensoren initialisieren
    pinMode(ADC_SENSOR_1, INPUT);
    pinMode(ADC_SENSOR_2, INPUT);
    pinMode(ADC_SENSOR_3, INPUT);
    pinMode(ADC_SENSOR_4, INPUT);

    // Digitale Eingänge initialisieren
    pinMode(DIGITAL_INPUT_1, INPUT_PULLUP);
    pinMode(DIGITAL_INPUT_2, INPUT_PULLUP);
    pinMode(DIGITAL_INPUT_3, INPUT_PULLUP);
    pinMode(DIGITAL_INPUT_4, INPUT_PULLUP);

    // PAS Interrupt einrichten (z.B. DIGITAL_INPUT_1)
    attachInterrupt(digitalPinToInterrupt(DIGITAL_INPUT_1), pasInterruptHandler, RISING);
}

void Sensors::read(SensorReadings &data) {
    data.analog[0] = analogRead(ADC_SENSOR_1);
    data.analog[1] = analogRead(ADC_SENSOR_2);
    data.analog[2] = analogRead(ADC_SENSOR_3);
    data.analog[3] = analogRead(ADC_SENSOR_4);

    data.digital[0] = !digitalRead(DIGITAL_INPUT_1);
    data.digital[1] = !digitalRead(DIGITAL_INPUT_2);
    data.digital[2] = !digitalRead(DIGITAL_INPUT_3);
    data.digital[3] = !digitalRead(DIGITAL_INPUT_4);
}


void Sensors::process(const SensorReadings &raw, float &throttle, bool &pasActive, uint8_t &hallState, bool buttons[2]) {
    throttle = processThrottle(raw.analog[0]);

    // PAS-Status: aktiv, wenn seit letztem Aufruf ein Impuls kam
    static uint32_t lastPasTickCount = 0;
    uint32_t currentPasTickCount = getPasTickCount();
    pasActive = (currentPasTickCount != lastPasTickCount);
    lastPasTickCount = currentPasTickCount;

    // Hall-Sensoren (z.B. digitale Eingänge 2+3)
    hallState = (raw.digital[1] << 1) | raw.digital[2];

    // Buttons (z.B. digital 4, zweiter Platz für Erweiterungen)
    buttons[0] = raw.digital[3];
    buttons[1] = false; // Erweiterbar für weiteren Button
}
