#include "Cube.h"

#include "../../parser/ObjParser.h";
#include "../../Game.h"

void Cube::render(std::shared_ptr<Camera> camera)
{
    GameObject::render(camera);
}

void Cube::update()
{
    GameObject::update();
}

void Cube::create(std::shared_ptr<PhongShader> shader)
{
    GameObject::create(shader);

	ObjParser parser("data/models/cube.obj");
    int triangles = parser.getTriangleCount();
	std::vector<float> vbo;
    parser.getDrawArraysGeo(vbo);
	Mesh* g = new Mesh(vbo.data(), vbo.size(), triangles, *this->shader);
	this->mesh = std::shared_ptr<Mesh>(g);
}

