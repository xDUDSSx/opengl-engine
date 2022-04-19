#include "Quad.h"

void Quad::render(std::shared_ptr<Camera> camera) const
{
    //// setup parallel projection
    //glm::mat4 orthoProjectionMatrix = glm::ortho(
    //    -1.0f, 1.0f,
    //    -1.0f, 1.0f,
    //    0.1f, 10.0f);
    //// static viewpoint - top view
    //glm::mat4 orthoViewMatrix = glm::lookAt(
    //    glm::vec3(0.0f, 1.0f, 1.0f),
    //    glm::vec3(0.0f, 0.0f, 0.0f),
    //    glm::vec3(0.0f, 1.0f, 0.0f));

    //// setup camera & projection transform
    //glm::mat4 viewMatrix = orthoViewMatrix;
    //glm::mat4 projectionMatrix = orthoProjectionMatrix;

    //glm::mat4 model = glm::mat4(1.0f);
    ////model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));

    //shader->setTransformUniforms(model, orthoViewMatrix, orthoProjectionMatrix);

    //glm::mat4 pvm = orthoProjectionMatrix * orthoViewMatrix * model;
	//glm::vec4 pos = pvm * glm::vec4(-0.5f, -0.5f, 0.0f, 0.0f);

	//printf("render:\n");
	//printf("Test pos: %f %f %f %f\n", pos.x, pos.y, pos.z, pos.w);
	//printf("Matrix 0: %f %f %f %f\n", pvm[0].x, pvm[0].y, pvm[0].z, pvm[0].w);
    //printf("Matrix 1: %f %f %f %f\n", pvm[1].x, pvm[1].y, pvm[1].z, pvm[1].w);
    //printf("Matrix 2: %f %f %f %f\n", pvm[2].x, pvm[2].y, pvm[2].z, pvm[2].w);
    //printf("Matrix 3: %f %f %f %f\n", pvm[3].x, pvm[3].y, pvm[3].z, pvm[3].w);

    glm::mat4 model = glm::mat4(1.0f);

    camera->matrix(*this->shader, model);

    glBindVertexArray(geometry->vao);
    glDrawElements(GL_TRIANGLES, geometry->triangleCount * 3, GL_UNSIGNED_INT, nullptr);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	CHECK_GL_ERROR();

    glBindVertexArray(0);
}

void Quad::create(std::shared_ptr<PhongShader> shader)
{
    this->shader = shader;

 //   unsigned int verticiesCount = 4 * 11;
 //   float vertices[] = {
 //       // positions      // colors         //tex coord // normals
 //       0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
 //       0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom right
 //       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
 //       -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
 //   };
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

	MeshGeometry* g = new MeshGeometry(vertices, verticiesCount, indices, indicesCount, triangles, *this->shader);
	this->geometry = std::shared_ptr<MeshGeometry>(g);
}
