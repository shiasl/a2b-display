#pragma once
#include <Arduino.h>

struct SensorReadings {
    uint16_t analog[4];
    bool digital[4];
};

class Sensors {
public:
    void begin();
    void read(SensorReadings &data);
    void process(const SensorReadings &raw, float &throttle, bool &pasActive, uint8_t &hallState, bool buttons[2]);
};

uint32_t getPasTickCount();
