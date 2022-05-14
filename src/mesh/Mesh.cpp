#include "pgr.h"

#include "Mesh.h"

Mesh::Mesh(MeshType type, float* verts, const int vertsCount, unsigned int* indices, const int indicesCount, const unsigned int triangleCount, PhongShader& shader)
	: type(type)
	, verts(verts)
	, indices(indices)
	, vertsCount(vertsCount)
	, indiciesCount(indicesCount) 
	, elementCount(triangleCount)
{
	initDrawElements(verts, vertsCount, indices, indiciesCount, shader);
}

Mesh::Mesh(MeshType type, float* verts, const int vertsCount, const unsigned int triangleCount, PhongShader& shader)
	: type(type)
	, verts(verts)
	, vertsCount(vertsCount)
	, elementCount(triangleCount)
{
	initDrawArrays(verts, vertsCount, shader);
}

void Mesh::render() const
{
    if (type == UNINITIALIZED) {
        pgr::dieWithError("Cannot render an uninitialized mesh!");
    	return;
    }
	glBindVertexArray(vao);
	switch (type) {
        default:
		case TRIANGLES_ARRAYS: 
			glDrawArrays(GL_TRIANGLES, 0, elementCount * 3);
			break;
		case TRIANGLES_ELEMENTS: 
			glDrawElements(GL_TRIANGLES, elementCount * 3, GL_UNSIGNED_INT, nullptr);    
			break;
	//  case LINES_ARRAYS:
	//      glDrawArrays(GL_LINES, 0, elementCount);
	//      break;
	}
	CHECK_GL_ERROR();
	glBindVertexArray(0);
}

void Mesh::dispose() const {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
}

void Mesh::initDrawElements(float* verts, int vertsCount, unsigned int* indices, int indicesCount, PhongShader& shader)
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertsCount * sizeof(float), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	const size_t vertexSize = 11 * sizeof(float);
	
	glEnableVertexAttribArray(shader.aPos);
	glVertexAttribPointer(shader.aPos, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0);

	glEnableVertexAttribArray(shader.aTexCoord);
	glVertexAttribPointer(shader.aTexCoord, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(shader.aNormal);
	glVertexAttribPointer(shader.aNormal, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(5 * sizeof(float)));

	glEnableVertexAttribArray(shader.aTangent);
	glVertexAttribPointer(shader.aTangent, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(8 * sizeof(float)));

	CHECK_GL_ERROR();

	glBindVertexArray(0);
}

void Mesh::initDrawArrays(float* verts, int vertsCount, PhongShader& shader)
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertsCount * sizeof(float), verts, GL_STATIC_DRAW);

	const size_t vertexSize = 11 * sizeof(float);

	glEnableVertexAttribArray(shader.aPos);
	glVertexAttribPointer(shader.aPos, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0);

	glEnableVertexAttribArray(shader.aTexCoord);
	glVertexAttribPointer(shader.aTexCoord, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(shader.aNormal);
	glVertexAttribPointer(shader.aNormal, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(5 * sizeof(float)));

	glEnableVertexAttribArray(shader.aTangent);
	glVertexAttribPointer(shader.aTangent, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(8 * sizeof(float)));

	CHECK_GL_ERROR();

	glBindVertexArray(0);
}
