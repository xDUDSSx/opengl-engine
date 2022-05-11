#include "Quad.h"

void Quad::create(PhongShader* shader)
{
    GameObject::create(shader);

    addEmptyMaterial();
    addEmptyTextureSet();

    //Create mesh
    unsigned int verticiesCount = 4 * 11;
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f , 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    };
	unsigned int indicesCount = 6;
    unsigned int indices[] = {
        0, 2, 1,
        2, 0, 3
    };
    unsigned int triangles = 2;

	Mesh* g = new Mesh(MeshType::TRIANGLES_ELEMENTS, vertices, verticiesCount, indices, indicesCount, triangles, *this->shader);
    this->meshes.push_back(std::shared_ptr<Mesh>(g));
}
