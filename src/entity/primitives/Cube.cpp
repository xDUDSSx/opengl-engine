#include "Cube.h"

#include "../../parser/ObjParser.h";

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

    // Load model
	ObjParser parser("data/models/cube.obj");
    int triangles = parser.getTriangleCount();
	std::vector<float> vbo;
    parser.getDrawArraysGeo(vbo);
	Mesh* g = new Mesh(vbo.data(), vbo.size(), triangles, *this->shader);
	this->mesh = std::shared_ptr<Mesh>(g);

    // Load texture
    this->texture = std::make_shared<Texture>("data/textures/container2.png", "diffuse");
    this->specularMap = std::make_shared<Texture>("data/textures/container2_specular.png", "specular");
}

