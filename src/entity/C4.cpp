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
    const auto tSet = std::make_shared<TextureSet>();
    tSet->texture = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_color.png", "diffuse");
    tSet->specularMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_specular.png", "specular");
    tSet->normalMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_normal.png", "normal");
    tSet->aoMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_ao.png", "ao");
    tSet->emissionMap = std::make_shared<Texture>("data/textures/c4/c4bakeFinal.001_emission.png", "emission");

    this->textureSets.push_back(tSet);

	
}
