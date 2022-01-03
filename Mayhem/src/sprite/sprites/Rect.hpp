#ifndef RECT_H
#define RECT_H

#include "../Sprite.hpp"

#include "../../../../include/vendor/glew-2.2.0/include/GL/glew.h"

#include "../../math/vector/Vector4f.hpp"

namespace Mayhem {
    namespace Draw {
        namespace Sprite2D {
            class Rect : public BaseSprite {
                private:
                    unsigned int VAO, VBO, EBO;
                    Vertex* vertices;
                    uint8_t indices[6];
                       
                    void generateVertices();
                    void generateIndices();

                    void setupVBO();
                public:
                    ~Rect();
                    void init() override;
                    void render() override;
                    void regenVBOAttributes() override;
            };
        }
    }
}


#endif /* ifndef RECT_H */
