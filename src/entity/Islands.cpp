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
	loadMesh("data/models/islands.obj", true);

	// Load textures
    const auto tSet = std::make_shared<TextureSet>();
    tSet->texture = std::make_shared<Texture>("data/textures/islands/Rock-cold_Albedo.jpg", "diffuse");
    //tSet->specularMap = std::make_shared<Texture>("data/textures/airship/123_air Ship_Specular.png", "specular");
    //tSet->normalMap = std::make_shared<Texture>("data/textures/airship/123_air Ship_Normal.png", "normal");
    this->textureSets.push_back(tSet);
}
