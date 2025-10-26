#include "core.h"

#include "logger.h"

#include <Arduino.h>

namespace core {
void init() {
#if (USE_SERIAL)
  Serial.begin(SERIAL_BAUD);
  Logger::debug("Serial initialized");
#endif

#if (BUILD_DEBUG)
  delay(5000); // Wait for serial to initialize
#endif
}

void loop() {}
} // namespace core