#include "Shader.hpp"

Mayhem::Utils::Shader::~Shader() {
    glDeleteProgram(shaderProgram);
    std::cout << "Deleting shaders!! -> " << (std::string)shaderPath << std::endl;
}

Mayhem::Utils::Shader::Shader(const char* shaderPath) {
    std::ifstream myShaderFile;
    std::string line;

    std::string source;
    myShaderFile.open(shaderPath);

    if (!myShaderFile.is_open()) {
        std::cout << "ERROR::FILE::NOT::FOUND >> " << shaderPath << std::endl;
        exit(EXIT_FAILURE);
    } else {
        this->shaderPath = shaderPath;

        while (getline(myShaderFile, line)) {
            source += line;
            source += "\n";
        }
    }

    std::regex type_regex("(#type)( )+([a-zA-Z]+)");
    std::smatch res;

    std::sregex_token_iterator iter(source.begin(),
            source.end(),
            type_regex,
            -1);
    std::sregex_token_iterator end;

    for ( ; iter != end; ++iter) {
        shaderSources.push_back(*iter);
    }

    vertexShaderSource = shaderSources[1].c_str();
    fragmentShaderSource = shaderSources[2].c_str();

    myShaderFile.close();
}


void Mayhem::Utils::Shader::compile() {
    // ===============================
    // VERTEX SHADER
    // ===============================

    // Create both vertex and fragment shader variables
    
    // Create vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Send shader source to vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // Compile shader
    glCompileShader(vertexShader);

    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    // ===============================
    // FRAGMENT SHADER
    // ===============================

    // Create shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Send source to shader 
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile shader
    glCompileShader(fragmentShader);

    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    // Link shaders to a shader program to use for rendering;

    shaderProgram = glCreateProgram();

    // Link attributes
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for errors 

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}



Mayhem::Utils::Shader::Shader(const char* vertexPath, const char* fragmentPath) {
}

Mayhem::Utils::Shader::Shader() {
}

char* Mayhem::Utils::Shader::getFilePath() {
    return (char*)shaderPath;
}

void Mayhem::Utils::Shader::use() {
    if (!beingUsed) {
        glUseProgram(shaderProgram);
        beingUsed = true;
    } 
}

void Mayhem::Utils::Shader::detach() {
    glUseProgram(0);
    beingUsed = false;
}

unsigned int Mayhem::Utils::Shader::getProgram() {
    return shaderProgram;
}

// Sending info methods

void Mayhem::Utils::Shader::sendMat4(const char* name, glm::mat4 mat) {
    use();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Mayhem::Utils::Shader::sendFloat(const char* name, float val) {
    use();
    glUniform1f(glGetUniformLocation(shaderProgram, name), val);
}


void Mayhem::Utils::Shader::sendInt(const char* name, int val) {
    use();
    glUniform1i(glGetUniformLocation(shaderProgram, name), val);
}
