#include <Arduino.h>

#include "core/core.h"
#include "user/user.h"

void setup() {
    core::init();
    user::init();
}

void loop() {
    core::loop();
    user::loop();
}
