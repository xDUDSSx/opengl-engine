#include "Cube.h"

#include "../parser/ObjParser.h";

void Cube::render(std::shared_ptr<Camera> camera) const
{
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

    camera->matrix(*this->shader, model);

    glBindVertexArray(geometry->vao);
    glDrawElements(GL_TRIANGLES, geometry->triangleCount * 3, GL_UNSIGNED_INT, nullptr);
    CHECK_GL_ERROR();

    glBindVertexArray(0);
}

void Cube::create(std::shared_ptr<PhongShader> shader)
{
    this->shader = shader;

	ObjParser parser("teapot_smooth.obj");
    int triangles = parser.getTriangleCount();
	std::vector<float> vbo;
    std::vector<unsigned int> ebo;
    parser.getDrawElementsGeo(vbo, ebo);
	MeshGeometry* g = new MeshGeometry(vbo.data(), vbo.size(), ebo.data(), ebo.size(), triangles, *this->shader);
	this->geometry = std::shared_ptr<MeshGeometry>(g);
}

