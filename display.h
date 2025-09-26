#pragma once
#include <Arduino.h>

class Display {
public:
    void begin();
    void showStatus(float throttle, bool pasActive, uint8_t hallState, bool buttons[2]);
};