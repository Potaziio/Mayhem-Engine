#include "Texture.hpp"

namespace Mayhem::Utils {
    Texture::~Texture() {
        glDeleteTextures(1, &textureID);
    }
    
    Texture::Texture() {}
	
	void Texture::init(const char* filepath) {
		stbi_set_flip_vertically_on_load(true);
        data = stbi_load(filepath, &width, &height, &nrChannels, 0);
        
        if (!isGood()) {
            std::cout << "ERROR:TEXTURE::FAILED_TO_LOAD_TEXTURE" << std::endl;
            exit(EXIT_FAILURE);
        }
        else {
            this->filepath = filepath;
            // Generate and bind texture
            
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            
            // Set texture parameters of currently bound texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            
            if (nrChannels == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
                glGenerateMipmap(GL_TEXTURE_2D);
            } else if (nrChannels == 4) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); 
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "ERROR::TEXTURE::UKNOWN_FILE_FORMAT" << std::endl;
                exit(EXIT_FAILURE);
            }
            
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        freeImageMem();
	}
    
    void Texture::bind() {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    
    void Texture::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    unsigned int Texture::getTextureID() {
        return textureID;
    }
    
    int Texture::getWidth() { 
        return width;
    }
    
    int Texture::getHeight() {
        return height;
    }
    
    void Texture::freeImageMem() {
        stbi_image_free(data);
    }
    
    bool Texture::isGood() {
        return data;
    }
    
    unsigned char* Texture::getData() {
        return data;
    }
}
