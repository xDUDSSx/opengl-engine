#include "Capacitor.h"
#include "../Game.h"

void Capacitor::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void Capacitor::update()
{
	GameObject::update();
	//rotation.z = Game::time * 60;
	//this->position += Game::time * 0.01f;
}

void Capacitor::create(PhongShader* shader)
{
	GameObject::create(shader);

	auto material = std::make_shared<Material>();
	material->shininess = 24;
	materials.push_back(material);

	// Load model
	loadMesh("data/models/capacitor1.obj", true);

	// Load texture
	const auto tSet = std::make_shared<TextureSet>();
	tSet->texture = Game::textures->load("data/textures/capacitor/capacitor_base_color.png", "diffuse");
	// tSet->specularMap = Game::textures->load("data/textures/container2_specular.png", "specular");
	tSet->normalMap = Game::textures->load("data/textures/capacitor/capacitor_base_normal.png", "normal");

	this->textureSets.push_back(tSet);

	
}
