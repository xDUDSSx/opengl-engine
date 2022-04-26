#include "GameObject.h"

#include "../../parser/ObjParser.h"

GameObject::GameObject() : Entity()
{
	// Empty
}

void GameObject::render(PhongShader& shader, Camera& camera)
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, transform.pos);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rot.x), glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rot.y), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rot.z), glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, transform.scale);

	// Apply transform
	camera.matrix(shader, modelMatrix);

	// Apply material
	material->setUniforms(shader);

	// Apply texture / maps
	if (texture != nullptr) {
		texture->bind(0, 0, shader);
	}
	if (specularMap != nullptr) {
		specularMap->bind(0, 1, shader);
	}
    if (normalMap != nullptr) {
        normalMap->bind(0, 2, shader);
    }
	if (aoMap != nullptr) {
		aoMap->bind(0, 3, shader);
	}
    if (emissionMap != nullptr) {
        emissionMap->bind(0, 4, shader);
    }

	mesh->render();

	// Clear texture state
	shader.clearTextures();
}

void GameObject::update()
{
	// Empty
}

void GameObject::create(std::shared_ptr<PhongShader> shader)
{
	this->shader = shader;
	this->material = std::make_shared<Material>();
}

void GameObject::loadMesh(const char* path, bool arraysOrElements) {
    loadMesh(path, arraysOrElements, 1.0f);
}

void GameObject::loadMesh(const char* path, bool arraysOrElements, float uvScale) {
    ObjParser parser(path, uvScale);
    int triangles = parser.getTriangleCount();
    std::vector<float> vbo;
    Mesh* g = nullptr;
    if (arraysOrElements) {
        parser.getDrawArraysGeo(vbo);
        g = new Mesh(vbo.data(), vbo.size(), triangles, *this->shader);
    } else {
        std::vector<unsigned int> ebo;
        parser.getDrawElementsGeo(vbo, ebo);
        g = new Mesh(vbo.data(), vbo.size(), ebo.data(), ebo.size(), triangles, *this->shader);
    }
    this->mesh = std::shared_ptr<Mesh>(g);
}
