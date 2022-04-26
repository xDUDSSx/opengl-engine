#version 330 core

layout (location = 0) in vec3 aPos;
  
out vec3 TexCoords;

uniform mat4 pvMatrix;

void main()
{
	gl_Position = pvMatrix * vec4(aPos, 1.0);
	TexCoords = aPos;
}    