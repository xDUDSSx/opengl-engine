#include "Quad.h"

void Quad::render(std::shared_ptr<Camera> camera)
{
    GameObject::render(camera);
}

void Quad::create(std::shared_ptr<PhongShader> shader)
{
    GameObject::create(shader);

    unsigned int verticiesCount = 4 * 8;
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f , 0.0f, 1.0f,
    };
	unsigned int indicesCount = 6;
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int triangles = 2;

	Mesh* g = new Mesh(vertices, verticiesCount, indices, indicesCount, triangles, *this->shader);
	this->mesh = std::shared_ptr<Mesh>(g);
}
