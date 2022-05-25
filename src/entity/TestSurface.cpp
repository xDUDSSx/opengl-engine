#include "TestSurface.h"
#include "../Game.h"

void TestSurface::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void TestSurface::update()
{
	GameObject::update();
}

void TestSurface::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load model
	loadMesh("data/models/test.obj", true, 4.0f);

	auto material = std::make_shared<Material>();
	material->shininess = 64;
	materials.push_back(material);

	// Load texture
	const auto tSet = std::make_shared<TextureSet>();
	tSet->texture = Game::textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-diffuse.jpg", "diffuse");
	tSet->specularMap = Game::textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-specular2.jpg", "specular");
	tSet->aoMap = Game::textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-ao.jpg", "ao");
	tSet->normalMap = Game::textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-normal.jpg", "normal");

	this->textureSets.push_back(tSet);


}
