#include "controller.h"

Controller controller;

void setup() {
    controller.begin();
}

void loop() {
    controller.update();
}