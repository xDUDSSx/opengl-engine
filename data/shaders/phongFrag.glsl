#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

uniform vec3 viewPos;
uniform sampler2D sampler;
uniform vec3 uniformColor;
uniform bool useTexture;

void main() {
	vec3 l_dir_world = vec3(5, 5, 5);
	vec3 l_dir = normalize((viewMatrix * modelMatrix * vec4(l_dir_world, 0.0)).xyz);

	vec3 diffuse = vec3(0.6, 0.3, 0.3);
	vec3 ambient = diffuse * 0.3f;
	vec3 specular = vec3(0.7, 0.7, 0.7);
	float shininess = 4.0f;

	vec3 L = l_dir;
	vec3 N = normalize(Normal);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(-FragPos);

	vec3 ambientLight = ambient;
	vec3 diffuseLight = diffuse * max(0.0, dot(N, L));
	vec3 specularLight = specular * pow(max(0.0, dot(R, V)), shininess);

	vec3 outColor = ambientLight + diffuseLight + specularLight;

	FragColor = vec4(outColor, 1.0);
}