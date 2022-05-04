#include "Islands.h"

void Islands::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void Islands::update()
{
	GameObject::update();
}

void Islands::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load model
	loadMesh("data/models/islands.obj", true, 5);

	// Load textures
    const auto tSet = std::make_shared<TextureSet>();
    tSet->texture = std::make_shared<Texture>("data/textures/islands/Rock-cold_Albedo_light.jpg", "diffuse");
	tSet->specularMap = std::make_shared<Texture>("data/textures/islands/Rock_Specular.jpg", "specular");
    tSet->normalMap = std::make_shared<Texture>("data/textures/islands/Rock_Normal-s.jpg", "normal");
    tSet->aoMap = std::make_shared<Texture>("data/textures/islands/Rock_AO.jpg", "ao");
    this->textureSets.push_back(tSet);
}
