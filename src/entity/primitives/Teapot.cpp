#include "Teapot.h"

#include "../../parser/ObjParser.h"
#include "../../Game.h"

void Teapot::render(PhongShader& shader, Camera& camera)
{
    GameObject::render(shader, camera);
}

void Teapot::update()
{
    GameObject::update();
    transform.rot.z = Game::time * 60;
    //scale = glm::vec3(cos(Game::time) * 0.5f);
}

void Teapot::create(std::shared_ptr<PhongShader> shader)
{
    GameObject::create(shader);

    loadMesh("data/models/teapot_smooth.obj", false);
}

