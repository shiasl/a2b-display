#pragma once
#include "sensors.h"
#include "display.h"

class Controller {
public:
    void begin();
    void update();

private:
    Sensors sensors;
    Display display;

    // Daten für Status
    SensorReadings raw;
    float throttle = 0;
    bool pasActive = false;
    uint8_t hallState = 0;
    bool buttons[2] = {false};

    // Timer für Anzeige/Serielle Ausgabe
    unsigned long lastDisplayUpdate = 0;
    const unsigned long displayUpdateInterval = 100; // ms
};