#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;

uniform mat4 viewMatrix;

uniform sampler2D	diffuse0;
uniform bool		diffuse0_active = false;

uniform sampler2D	specular0;
uniform bool		specular0_active = false;

uniform sampler2D	ao0;
uniform bool		ao0_active = false;

uniform sampler2D	normal0;
uniform bool		normal0_active = false;

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

struct SpotLight {
	vec3 position;
	vec3 direction;
	
	float cutoffAngle;
	float cutoffSoftAngle;
	float radius;

	float intensity;
	vec3 color;
};

#define MAX_POINT_LIGHTS 25
#define MAX_SUN_LIGHTS 10
#define MAX_SPOT_LIGHTS 20

uniform int pointLightsCount;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform int sunLightsCount;
uniform SunLight sunLights[MAX_SUN_LIGHTS];

uniform int spotLightsCount;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

//float map(float value, float min1, float max1, float min2, float max2) {
//	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
//}

vec3 calculateAmbientLight(vec3 lightColor, vec3 ambient) {
	return lightColor * ambient * (diffuse0_active ? vec3(texture(diffuse0, TexCoords)) : vec3(1));
}

vec3 calculateDiffuseLight(vec3 lightColor, vec3 diffuse, vec3 N, vec3 L) {
	return lightColor * diffuse * max(0.0, dot(N, L)) * (diffuse0_active ? vec3(texture(diffuse0, TexCoords)) : vec3(1));
}

vec3 calculateSpecularLight(vec3 lightColor, vec3 specular, vec3 R, vec3 V, float shininess) {
	return lightColor * specular * pow(max(0.0, dot(R, V)), material.shininess) * (specular0_active ? vec3(texture(specular0, TexCoords)) : vec3(1));
}

float calculateAttenuation(float dist, float radius) {
	float constant = 1.0;
	float linear = 0.09f;
	float quadratic = 0.032f;

	//float attenuation = clamp(1.0 / (1.0 + 0.0 * lightDist + 1.0 * lightDist * lightDist), 0.0, 1.0);
	//float attenuation = pow(clamp(1.0 - dist*dist/(radius*radius), 0.0, 1.0), 2);
	float attenuation = pow(clamp(1.0 - dist/(radius), 0.0, 1.0), 2);
	//float attenuation = 1.0 / (constant + linear * dist + quadratic * (dist * dist));
	return attenuation;
}

vec3 calculateSunLight(SunLight light, Material material, vec3 fragPos, vec3 normal) {
	vec3 lightDir = (viewMatrix * vec4(light.direction, 0.0)).xyz;
	vec3 fragToLight = -lightDir;
	vec3 L = normalize(fragToLight);
	vec3 N = normalize(normal);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(-fragPos);

	vec3 ambientLight = calculateAmbientLight(light.color, material.ambient);
	vec3 diffuseLight = calculateDiffuseLight(light.color, material.diffuse, N, L);
	vec3 specularLight = calculateSpecularLight(light.color, material.specular, R, V, material.shininess);

	specularLight *= 0.3f; //Turn down sun specular a bit

	return light.intensity * (ambientLight + diffuseLight + specularLight);
}

vec3 calculateSpotLight(SpotLight light, Material material, vec3 fragPos, vec3 normal) {
	vec3 lightPos = (viewMatrix * vec4(light.position, 1.0)).xyz;
	vec3 lightDir = (viewMatrix * vec4(light.direction, 0.0)).xyz;

	vec3 fragToLight = lightPos - fragPos;
	float lightDist = length(fragToLight);
	float lightRadius = light.radius;
	vec3 L = normalize(fragToLight);
	vec3 N = normalize(normal);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(-fragPos);
	vec3 S = normalize(lightDir);

	vec3 ambientLight = calculateAmbientLight(light.color, material.ambient);
	vec3 diffuseLight = calculateDiffuseLight(light.color, material.diffuse, N, L);
	vec3 specularLight = calculateSpecularLight(light.color, material.specular, R, V, material.shininess);

	vec3 outColor = vec3(0);

	float fragAngle = radians(90.0f) * max(0.0, dot(-L, S));
	if (fragAngle >= light.cutoffAngle) {
		float attenuation = calculateAttenuation(lightDist, lightRadius);
		float softFlatDiff = light.cutoffSoftAngle - light.cutoffAngle;
		float softFactor = clamp((fragAngle - light.cutoffAngle) / softFlatDiff, 0.0, 1.0);
		outColor = smoothstep(0.0, 1.0, softFactor) * light.intensity * attenuation * (ambientLight + diffuseLight + specularLight);
	} else {
		outColor *= 0;
	}
	return outColor;
}

vec3 calculatePointLight(PointLight light, Material material, vec3 fragPos, vec3 normal) {
	// Normal mapping
	if (normal0_active) {
		normal = texture(normal0, TexCoords).rgb;
		//normal = vec3(normal.x, 1.0f - normal.y, normal.z);
		normal = normalize(normal * 2.0 - 1.0); // from [0, 1] to [-1, 1]
		normal = normalize(mat3(Tangent, Binormal, Normal) * normal); // from tangent space to view space
	}

	vec3 lightPos = (viewMatrix * vec4(light.position, 1.0)).xyz;
	vec3 fragToLight = lightPos - fragPos;
	float lightDist = length(fragToLight);
	float lightRadius = light.radius;
	vec3 L = normalize(fragToLight);
	vec3 N = normalize(normal);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(-fragPos);

	vec3 ambientLight = calculateAmbientLight(light.color, material.ambient);
	vec3 diffuseLight = calculateDiffuseLight(light.color, material.diffuse, N, L);
	vec3 specularLight = calculateSpecularLight(light.color, material.specular, R, V, material.shininess);

	float attenuation = calculateAttenuation(lightDist, lightRadius);

	return light.intensity * attenuation * (ambientLight + diffuseLight + specularLight);
}

void main() {
	vec3 outColor = vec3(0);
	for (int i = 0; i < sunLightsCount; i++) {
		outColor += calculateSunLight(sunLights[i], material, FragPos, Normal);
	}
	for (int i = 0; i < pointLightsCount; i++) {
		outColor += calculatePointLight(pointLights[i], material, FragPos, Normal);
	}
	for (int i = 0; i < spotLightsCount; i++) {
		outColor += calculateSpotLight(spotLights[i], material, FragPos, Normal);
	}

	FragColor = vec4(outColor, 1.0);
}