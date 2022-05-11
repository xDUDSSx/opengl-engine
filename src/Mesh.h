#pragma once

#include "pgr.h"

#include "shader/PhongShader.h"

enum MeshType {
	TRIANGLES_ARRAYS, TRIANGLES_ELEMENTS,
	UNINITIALIZED
};

class Mesh {
public:
    MeshType type = UNINITIALIZED;

	float* verts;
	unsigned int* indices = nullptr;

	unsigned int vertsCount;
	unsigned int indiciesCount = -1;

	unsigned int elementCount; // ~ triangle count

	GLuint vbo = -1;
	GLuint ebo = -1;
	GLuint vao = -1;

	Mesh() = default;
	Mesh(MeshType type, float* verts, int vertsCount, unsigned int* indices, int indicesCount, unsigned int triangleCount, PhongShader& shader);
	Mesh(MeshType type, float* verts, int vertsCount, unsigned int triangleCount, PhongShader& shader);

	void render() const;
	void dispose() const;

private:
    void initDrawElements(float* verts, int vertsCount, unsigned int* indices, int indicesCount, PhongShader& shader);
    void initDrawArrays(float* verts, int vertsCount, PhongShader& shader);
	//std::array<bool, 5> attr
};
