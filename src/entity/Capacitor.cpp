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

void Capacitor::create(std::shared_ptr<PhongShader> shader)
{
	GameObject::create(shader);

	material->shininess = 24;

	// Load model
    loadMesh("data/models/capacitor1.obj", true);

	// Load texture
	this->texture = std::make_shared<Texture>("data/textures/capacitor/capacitor_base_color.png", "diffuse");
	// this->specularMap = std::make_shared<Texture>("data/textures/container2_specular.png", "specular");
	this->normalMap = std::make_shared<Texture>("data/textures/capacitor/capacitor_base_normal.png", "normal");
}
