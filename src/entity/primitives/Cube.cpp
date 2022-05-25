#include "Cube.h"
#include "../../Game.h"

void Cube::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void Cube::update()
{
	GameObject::update();
	transform.rot.z = Game::time * 60;
}

void Cube::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load model
	loadMesh("data/models/cube.obj", true);
	
	// Load texture
	const auto tSet = std::make_shared<TextureSet>();
	tSet->texture = Game::textures->load("data/textures/container2.png", "diffuse");
	tSet->specularMap = Game::textures->load("data/textures/container2_specular.png", "specular");
	tSet->emissionMap = Game::textures->load("data/textures/matrix2.png", "emission");

	this->textureSets.push_back(tSet);
}

