#include "C4.h"

void C4::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void C4::update()
{
	GameObject::update();
}

void C4::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load model
    loadMesh("data/models/c4.obj", true);
	
	// Load texture
	this->texture = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_color.png", "diffuse");
	this->specularMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_specular.png", "specular");
    this->normalMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_normal.png", "normal");
    this->aoMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_ao.png", "ao");
    this->emissionMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_emission.png", "emission");
}
