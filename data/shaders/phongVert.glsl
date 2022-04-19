#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 pvmMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec3 Color;
out vec2 TexCoord;

void main() {
    gl_Position = pvmMatrix * vec4(aPos, 1.0);

    FragPos = (viewMatrix * modelMatrix * vec4(aPos, 1.0)).xyz;
    Normal = normalize(viewMatrix * normalMatrix * vec4(aNormal, 0.0)).xyz;

    Color = vec3(1.0f, 0.0f, 0.0f);
    TexCoord = aTexCoord;
}