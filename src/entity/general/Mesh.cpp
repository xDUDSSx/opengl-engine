#include "pgr.h"

#include "Mesh.h"

Mesh::Mesh(float* verts, int vertsCount, unsigned int* indices, int indicesCount, int triangleCount, PhongShader& shader)
    : indiciesCount(indicesCount)
    , vertsCount(vertsCount)
    , indices(indices)
    , verts(verts)
    , triangleCount(triangleCount)
    , drawElementsMode(drawElementsMode)
{
	initDrawElements(verts, vertsCount, indices, indiciesCount, shader);
}

void Mesh::render() const {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, triangleCount * 3, GL_UNSIGNED_INT, nullptr);
    CHECK_GL_ERROR();

    glBindVertexArray(0);
}

void Mesh::initDrawElements(float* verts, int vertsCount, unsigned int* indices, int indicesCount, PhongShader& shader)
{
    drawElementsMode = true;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertsCount * sizeof(float), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    const size_t vertexSize = 8 * sizeof(float);
    
    glEnableVertexAttribArray(shader.aPos);
    glVertexAttribPointer(shader.aPos, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0);

    glEnableVertexAttribArray(shader.aTexCoord);
    glVertexAttribPointer(shader.aTexCoord, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(shader.aNormal);
    glVertexAttribPointer(shader.aNormal, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(5 * sizeof(float)));

    CHECK_GL_ERROR();

    glBindVertexArray(0);
}
