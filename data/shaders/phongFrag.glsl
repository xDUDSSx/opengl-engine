#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;

uniform mat4 viewMatrix;

uniform vec3 viewPos;
uniform sampler2D sampler;
uniform vec3 uniformColor;
uniform bool useTexture;

struct Material {
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
	float shininess;
};

uniform Material material;

struct PointLight {
	vec3 position;
	
	float radius;

	float intensity;
	vec3 color;
};

struct SunLight {
	vec3 direction;
	
	float intensity;
	vec3 color;
};

#define MAX_POINT_LIGHTS 25
#define MAX_SUN_LIGHTS 10

uniform int pointLightsCount;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform int sunLightsCount;
uniform SunLight sunLights[MAX_SUN_LIGHTS];

vec3 calculateSunLight(SunLight light, Material material, vec3 fragPos, vec3 normal) {
	vec3 lightDir = (viewMatrix * vec4(light.direction, 0.0)).xyz;
	vec3 fragToLight = -lightDir;
	vec3 L = normalize(fragToLight);
	vec3 N = normalize(normal);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(-fragPos);

	vec3 ambientLight = light.color * 0.3f * material.ambient;
	vec3 diffuseLight = light.color * material.diffuse * max(0.0, dot(N, L));
	vec3 specularLight = light.color * material.specular * pow(max(0.0, dot(R, V)), material.shininess);

	return light.intensity * (ambientLight + diffuseLight + specularLight);
}

vec3 calculatePointLight(PointLight light, Material material, vec3 fragPos, vec3 normal) {
	vec3 lightPos = (viewMatrix * vec4(light.position, 1.0)).xyz;
	vec3 fragToLight = lightPos - fragPos;
	float lightDist = length(fragToLight);
	float lightRadius = light.radius;
	vec3 L = normalize(fragToLight);
	vec3 N = normalize(normal);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(-fragPos);

	float constant = 1.0;
	float linear = 0.09f;
	float quadratic = 0.032f;

	vec3 ambientLight = light.color * 0.3f * material.ambient;
	vec3 diffuseLight = light.color * material.diffuse * max(0.0, dot(N, L));
	vec3 specularLight = light.color * material.specular * pow(max(0.0, dot(R, V)), material.shininess);

	//float attenuation = clamp(1.0 / (1.0 + 0.0 * lightDist + 1.0 * lightDist * lightDist), 0.0, 1.0);
	//float attenuation = clamp(1.0 - lightDist*lightDist/(lightRadius*lightRadius), 0.0, 1.0);
	float attenuation = 1.0 / (constant + linear * lightDist + quadratic * (lightDist * lightDist));    

	return light.intensity * attenuation * (ambientLight + diffuseLight + specularLight);
}

void main() {
	vec3 l_dir_world = vec3(1, 0, 1);
	vec3 l_dir = normalize((viewMatrix * vec4(l_dir_world, 0.0)).xyz);

	vec3 l_pos_world = vec3(3, 0, 0);
	vec3 l_pos = (viewMatrix * vec4(l_pos_world, 1.0)).xyz;
	
	vec3 outColor = vec3(0);
	for (int i = 0; i < sunLightsCount; i++) {
		outColor += calculateSunLight(sunLights[i], material, FragPos, Normal);
	}
	for (int i = 0; i < pointLightsCount; i++) {
		outColor += calculatePointLight(pointLights[i], material, FragPos, Normal);
	}

	FragColor = vec4(outColor, 1.0);
}