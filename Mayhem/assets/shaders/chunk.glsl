#type vertex
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTexCoords;
layout (location=2) in float alightLvl;

uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;
out float lightLvl;

void main() {
    TexCoords = aTexCoords;
    lightLvl = alightLvl;
    gl_Position = projection * view * vec4(aPos, 1.0f);
}

#type fragment
#version 330 core

out vec4 FragColor;

uniform sampler2D ourTexture;

in vec2 TexCoords;
in float lightLvl;

void main() {
    FragColor = texture(ourTexture, TexCoords) * vec4(lightLvl / 10.0f, lightLvl / 10.0f, lightLvl / 10.0f, 1.0f);
	//FragColor = texture(ourTexture, TexCoords);
}
