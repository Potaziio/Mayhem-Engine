#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

namespace Mayhem {
    namespace ECS {
        namespace Components {
            class Component {
                public:
                    virtual std::string GetComponentType() {}
                    virtual ~Component() {}
            };
        }
    }
}

#endif /* ifndef COMPONENT_H */
