#pragma once

#include "pgr.h"

#include "../shader/PhongShader.h"

enum MeshType {
	TRIANGLES_ARRAYS, TRIANGLES_ELEMENTS,
	UNINITIALIZED
};

/**
 * \brief A wrapper object managing OpenGL geometry data.
 * Supports drawArrays and drawElements geometry.
 * Vertex attributes are hardcoded and are:
 * - aPos (vec3)
 * - aTexCoord (vec2)
 * - aNormal (vec3)
 * - aTangent (vec3)
 */
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
	/**
	 * \brief Create drawElements geometry.
	 * \param type Geo type (currently just TRIANGLES_ELEMENTS)
	 * \param verts Vertex array 
	 * \param vertsCount Vertex array size
	 * \param indices Indices array
	 * \param indicesCount Indices array size
	 * \param triangleCount Triangle count
	 * \param shader Shader for vertex attribute ids
	 */
	Mesh(MeshType type, float* verts, int vertsCount, unsigned int* indices, int indicesCount, unsigned int triangleCount, PhongShader& shader);

	/**
	 * @brief Create drawArrays geometry.
	 * @param type Geo type (currently just TRIANGLES_ARRAYS)
	 * @param verts Vertex array 
	 * @param vertsCount Vertex array size
	 * @param triangleCount Triangle count
	 * @param shader Shader for vertex attribute ids
	*/
	Mesh(MeshType type, float* verts, int vertsCount, unsigned int triangleCount, PhongShader& shader);

	void render() const;
	void dispose() const;

private:
	void initDrawElements(float* verts, int vertsCount, unsigned int* indices, int indicesCount, PhongShader& shader);
	void initDrawArrays(float* verts, int vertsCount, PhongShader& shader);
	//std::array<bool, 5> attr
};
