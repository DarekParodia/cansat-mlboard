#include "core/core.h"
#include "user/user.h"

#include <Arduino.h>

void setup() {
    core::init();
    user::init();
}

void loop() {
    core::loop();
    user::loop();
}
