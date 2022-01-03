#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../../../include/vendor/stb_image/stb_image.h"

#include "../../../../include/vendor/glew-2.2.0/include/GL/glew.h"
#define GLFW_INCLUDE_NONE
#include "../../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"
#include <iostream>

namespace Mayhem {
    namespace Utils {
        class Texture {
            private:
            int width, height, nrChannels;
            unsigned char* data;
            unsigned int textureID;
            const char* filepath;
            public:
            ~Texture();
            Texture();
			
			void init(const char* filepath);
            
            unsigned char* getData();
            unsigned int getTextureID();
            
            void bind();
            void unbind();
            
            const char* getFilePath() {return filepath;}
            int getWidth();
            int getHeight();
            void freeImageMem();
            bool isGood();
        };
    }
}

#endif 
