#include "Cube.h"

#include "../../parser/ObjParser.h";
#include "../../Game.h"

void Cube::render(std::shared_ptr<Camera> camera)
{
    GameObject::render(camera);
}

void Cube::update() {
    GameObject::update();
	rotation.z = Game::time * 60;
    //scale = glm::vec3(cos(Game::time) * 0.5f);
}

void Cube::create(std::shared_ptr<PhongShader> shader)
{
    GameObject::create(shader);

	ObjParser parser("data/models/teapot_smooth.obj");
    int triangles = parser.getTriangleCount();
	std::vector<float> vbo;
    std::vector<unsigned int> ebo;
    parser.getDrawElementsGeo(vbo, ebo);
	Mesh* g = new Mesh(vbo.data(), vbo.size(), ebo.data(), ebo.size(), triangles, *this->shader);
	this->mesh = std::shared_ptr<Mesh>(g);
}

