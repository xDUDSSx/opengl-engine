#pragma once
#include "pgr.h"
#include <vector>
#include <array>

#include "ObjVertex.h"

class ObjParser {
public:
	ObjParser(const char* path);

    void getDrawArraysGeo(std::vector<float>& vbo);
    void getDrawElementsGeo(std::vector<float>& vbo, std::vector<unsigned int>& ebo);

    int getAttributesPerVertex() const;
    unsigned int getTriangleCount() const;

private:
    const int attributesPerVertex = 8;
    unsigned int triangleCount = 0;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    std::vector<ObjVertex> vboEntries;

    std::vector<std::array<int, 3>> vertexIndices;
    std::vector<std::array<int, 3>> uvIndices;
    std::vector<std::array<int, 3>> normalIndices;

    void parseObj(const char* path);
};
