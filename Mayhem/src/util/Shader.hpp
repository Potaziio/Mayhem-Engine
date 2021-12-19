#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include "../../../include/vendor/glew-2.2.0/include/GL/glew.h"

#include "../../../include/vendor/glm/glm/glm.hpp"
#include "../../../include/vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../../../include/vendor/glm/glm/gtc/type_ptr.hpp"

namespace Mayhem {
    namespace Utils {
        class Shader {
            private:
                unsigned int shaderProgram;
                const char* shaderPath;

                bool beingUsed;

                const char* vertexShaderSource;
                const char* fragmentShaderSource;

                unsigned int vertexShader;
                unsigned int fragmentShader;

                std::vector<std::string> shaderSources;

            public:
                Shader(const char* shaderPath);
                Shader(const char* vertexPath, const char* fragmentPath);   // Unimplemented
                Shader();    // Unimplemented
                ~Shader();

                void use();
                void compile();
                void detach();

                unsigned int getProgram();
                char* getFilePath();

                void sendFloat(const char* varName, float val);
                void sendInt(const char* varName, int val);
                void sendMat4(const char* varName, glm::mat4 mat);
                void sendMat3(const char* varName, glm::mat3 mat);
                void sendMat2(const char* varName, glm::mat2 mat); 
        };
    }
}

#endif
