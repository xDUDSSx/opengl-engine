#include "Airship.h"
#include "../Game.h"

void Airship::create(PhongShader* shader)
{
	GameObject::create(shader);

	addEmptyMaterial();
	addEmptyMaterial();

	// Load models
	//loadMesh("data/models/airship.obj", true); // Higher res model
	loadMesh("data/models/airship_decimated.obj", true);
	loadMesh("data/models/airship_windows_decimated.obj", true);

	// Load textures
	const auto tSet = std::make_shared<TextureSet>();
	tSet->texture = Game::textures->load("data/textures/airship/123_air Ship_BaseColor.png", "diffuse");
	tSet->specularMap = Game::textures->load("data/textures/airship/123_air Ship_Specular.png", "specular");
	tSet->normalMap = Game::textures->load("data/textures/airship/123_air Ship_Normal.png", "normal");
	this->textureSets.push_back(tSet);

	const auto tSetGlass = std::make_shared<TextureSet>();
	tSetGlass->texture = Game::textures->load("data/textures/airship/123_glass_BaseColor.png", "diffuse");
	tSetGlass->specularMap = Game::textures->load("data/textures/airship/123_glass_Specular.png", "specular");
	tSetGlass->normalMap = Game::textures->load("data/textures/airship/123_glass_Normal.png", "normal");
	this->textureSets.push_back(tSetGlass);

	opaque = false;
	backFaceCull = true;
}
