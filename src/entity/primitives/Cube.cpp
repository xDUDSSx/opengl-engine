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

void Cube::create(std::shared_ptr<PhongShader> shader)
{
    GameObject::create(shader);

    // Load model
    loadMesh("data/models/cube.obj", true);
    
    // Load texture
    this->texture = std::make_shared<Texture>("data/textures/container2.png", "diffuse");
    this->specularMap = std::make_shared<Texture>("data/textures/container2_specular.png", "specular");
    this->emissionMap = std::make_shared<Texture>("data/textures/matrix2.png", "emission");
}

