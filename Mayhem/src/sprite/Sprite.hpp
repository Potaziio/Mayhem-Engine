#ifndef SPRITE_H
#define SPRITE_H

#include "../math/vector/Vector4f.hpp"

namespace Mayhem {
    namespace Draw {
        namespace Sprite2D {
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
