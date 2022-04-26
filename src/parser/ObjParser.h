#pragma once
#include "pgr.h"
#include <vector>
#include <array>

#include "ObjVertex.h"

class ObjParser {
public:
	ObjParser(const char* path);
    ObjParser(const char* path, float uvScale);

	void getDrawArraysGeo(std::vector<float>& vbo);
	void getDrawElementsGeo(std::vector<float>& vbo, std::vector<unsigned int>& ebo);

	int getAttributesPerVertex() const;
	unsigned int getTriangleCount() const;

protected:
	const int attributesPerVertex = 8;
	unsigned int triangleCount = 0;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;

	std::vector<ObjVertex> vboEntries;

	std::vector<std::array<int, 3>> vertexIndices; //Start at 1
	std::vector<std::array<int, 3>> uvIndices; //Start at 1
	std::vector<std::array<int, 3>> normalIndices; //Start at 1
	std::vector<unsigned int> tangentIndices; //Start at 0

	void parseObj(const char* path);
    void parseObj(const char* path, float uvScale);
    void calculateTangents();
};
