#ifndef MAYHEMUTIL_H
#define MAYHEMUTIL_H

#include <iostream>
#include <random>
#include <sstream>

#define RGBANORM(r, g, b, a) (float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f

#define unimplemented() printf("This function '%s' is unimplemented...", __FUNCTION__); \
    exit(1)

namespace Mayhem {
    namespace Utils {
        class UUID {
            private:
                std::string m_id;
            public:
                UUID();
                std::string id() { return m_id; }
        }; 
    }
}


#endif /* ifndef MAYHEMUTIL_H */
