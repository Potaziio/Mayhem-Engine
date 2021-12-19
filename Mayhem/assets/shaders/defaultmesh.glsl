#type vertex
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec4 aColor;

out vec4 ourColor;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    ourColor = aColor;
}

#type fragment
#version 330 core

out vec4 FragColor;

in vec4 ourColor;

void main() {
    FragColor = ourColor;
}
