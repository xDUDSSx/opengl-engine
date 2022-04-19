#pragma once

#include "pgr.h";

#include "../../shader/PhongShader.h"

class MeshGeometry {
public:
    float* verts;
    unsigned int* indices;

    unsigned int vertsCount;
    unsigned int indiciesCount;
    unsigned int triangleCount;

    //bool color;
    //bool uv;
    //bool normals;

    GLuint vbo;
    GLuint ebo;
    GLuint vao;

    MeshGeometry(float* verts, const int vertsCount, unsigned int* indices, const int indicesCount, const int triangleCount, PhongShader& shader);

private:
    void init(float* verts, int vertsCount, unsigned int* indices, int indicesCount, PhongShader& shader);
};
