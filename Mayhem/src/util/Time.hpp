#ifndef TIME_H
#define TIME_H

#define GLFW_INCLUDE_NONE
#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"

namespace Mayhem {
    namespace Utils {
        class Time {
            private:
                static float dt;
                static float startTime;
                static float endTime;
            public:
                Time();

                static float deltaTime();

                static float GetMilliseconds();
        };    
    }
}

#endif /* ifndef TIME_H */
