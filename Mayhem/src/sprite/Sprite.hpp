#ifndef SPRITE_H
#define SPRITE_H

#include "../math/vector/Vector4f.hpp"

namespace Mayhem {
    namespace Draw {
        namespace Sprite2D {
            struct Vertex {
                int8_t position[3];
                int8_t color[4]; 
            };

            class BaseSprite {
                public:
                    Math::Vector4f color; 
                    virtual void init() {}
                    virtual void render() {}
                    virtual void regenVBOAttributes() {}
            };
        }
    }
}

#endif /* ifndef SPRITE_H */
