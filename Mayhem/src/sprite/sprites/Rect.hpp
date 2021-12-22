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
                    unsigned int indices[6];
                    float vertices[28];
                       
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
