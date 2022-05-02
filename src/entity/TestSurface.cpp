#include "TestSurface.h"

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

	// Load texture
    material->shininess = 64;
    texture = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-diffuse.jpg", "diffuse");
    specularMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-specular2.jpg", "specular");
    aoMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-ao.jpg", "ao");
    normalMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-normal.jpg", "normal");
}
