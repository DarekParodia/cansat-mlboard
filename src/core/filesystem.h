#pragma once

#include "FS.h"

#include <cstddef>
#include <stdint.h>

namespace core {
    void writeFile(fs::FS &fs, const char *path, uint8_t *data, size_t len);
} // namespace core