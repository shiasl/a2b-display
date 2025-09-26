#include "display.h"
#include "pinout.h"
// #include <Adafruit_GFX.h> // Replace with real driver for your display
// #include <Waveshare_1_47.h> // Placeholder

void Display::begin() {
    // Initialize display hardware here
    // display.begin();
}

void Display::showStatus(float throttle, bool pasActive, uint8_t hallState, bool buttons[2]) {
    // Replace with your display drawing routines
    Serial.print("Throttle: "); Serial.print(throttle, 2);
    Serial.print(" PAS: "); Serial.print(pasActive);
    Serial.print(" Hall: "); Serial.print(hallState);
    Serial.print(" Button0: "); Serial.print(buttons[0]);
    Serial.print(" Button1: "); Serial.println(buttons[1]);
}