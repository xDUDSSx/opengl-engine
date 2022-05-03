#include "Airship.h"

void Airship::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void Airship::update()
{
	GameObject::update();
}

void Airship::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load models
    //loadMesh("data/models/airship.obj", true); // Higher res model
	loadMesh("data/models/airship.obj", true);
    loadMesh("data/models/airship_windows.obj", true);

	// Load textures
    const auto tSet = std::make_shared<TextureSet>();
    tSet->texture = std::make_shared<Texture>("data/textures/airship/123_air Ship_BaseColor.png", "diffuse");
    tSet->specularMap = std::make_shared<Texture>("data/textures/airship/123_air Ship_Specular.png", "specular");
    tSet->normalMap = std::make_shared<Texture>("data/textures/airship/123_air Ship_Normal.png", "normal");
    this->textureSets.push_back(tSet);

    const auto tSetGlass = std::make_shared<TextureSet>();
    tSetGlass->texture = std::make_shared<Texture>("data/textures/airship/123_glass_BaseColor.png", "diffuse");
    tSetGlass->specularMap = std::make_shared<Texture>("data/textures/airship/123_glass_Specular.png", "specular");
    tSetGlass->normalMap = std::make_shared<Texture>("data/textures/airship/123_glass_Normal.png", "normal");
    this->textureSets.push_back(tSetGlass);

    opaque = false;
    backFaceCull = true;
}
