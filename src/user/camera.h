#pragma once

#include <string>

namespace user {
    class Camera {
        public:
            Camera();
            ~Camera();
            bool init();
            void savePicture(std::string filename);

        private:
            bool          initialized;
            unsigned long last_capture_time = 0;
    };
} // namespace user