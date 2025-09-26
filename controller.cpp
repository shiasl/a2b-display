#include "controller.h"

void Controller::begin() {
    sensors.begin();
    display.begin();
}

void Controller::update() {
    sensors.read(raw);
    sensors.process(raw, throttle, pasActive, hallState, buttons);

    // Anzeige/Serielle Ausgabe nur alle displayUpdateInterval ms
    unsigned long now = millis();
    if (now - lastDisplayUpdate > displayUpdateInterval) {
        display.showStatus(throttle, pasActive, hallState, buttons);
        lastDisplayUpdate = now;
    }

    // Hier später: CAN-Kommunikation, Motorsteuerung, etc.
}