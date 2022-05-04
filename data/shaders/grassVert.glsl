#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;

uniform float time;
uniform float windStrength;

uniform mat4 pvmMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;
out float Fog;

//Normal mapping stuff largely inspired from 
//https://lettier.github.io/3d-game-shaders-for-beginners/normal-mapping.html
//and
//https://learnopengl.com/Advanced-Lighting/Normal-Mapping

void main() {
	vec3 position = aPos;
	float offset = (sin(time) + sin(1.3 * time + 5.7)) * 0.5; // [-1, 1] 
	if (aTexCoords.y > 0.5) {
		position += (aTangent * offset * windStrength);
	}

	gl_Position = pvmMatrix * vec4(position, 1.0);
	FragPos = (viewMatrix * modelMatrix * vec4(position, 1.0)).xyz;

	Normal = normalize(viewMatrix * normalMatrix * vec4(aNormal, 0.0)).xyz;
	
	//Remaining view space normal basis vectors, used to convert from tangent space to view space in frag shader
	Tangent = normalize(viewMatrix * normalMatrix * vec4(aTangent, 0.0)).xyz;
	Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal); //Gram–Schmidt process
	Binormal = cross(Normal, Tangent); //Get third basis vector as a cross of the two existing orthogonal ones
	
	Fog = -FragPos.z;

	TexCoords = aTexCoords;
}