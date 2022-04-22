#pragma once

#include "pgr.h";

#include "../../shader/PhongShader.h"

class Mesh {
public:
    float* verts;
    unsigned int* indices = nullptr;

    unsigned int vertsCount;
    unsigned int indiciesCount = -1;

    unsigned int triangleCount;
    bool drawElementsMode;

    GLuint vbo = -1;
    GLuint ebo = -1;
    GLuint vao = -1;

    Mesh(float* verts, const int vertsCount, unsigned int* indices, const int indicesCount, const int triangleCount, PhongShader& shader);
    Mesh(float* verts, const int vertsCount, const int triangleCount, PhongShader& shader);

    void render() const;

private:
    void initDrawElements(float* verts, int vertsCount, unsigned int* indices, int indicesCount, PhongShader& shader);
    void initDrawArrays(float* verts, int vertsCount, PhongShader& shader);
};
