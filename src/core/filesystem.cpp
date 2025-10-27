#include "core/filesystem.h"

#include "core/logger.h"

namespace core {
    void writeFile(fs::FS &fs, const char *path, uint8_t *data, size_t len) {
        Logger::debug("Writing file: %s\r\n", path);

        File file = fs.open(path, FILE_WRITE);
        if(!file) {
            Logger::error("Failed to open file for writing");
            return;
        }
        if(file.write(data, len) == len)
            Logger::debug("File written");
        else
            Logger::error("Write failed");
        file.close();
    }
} // namespace core