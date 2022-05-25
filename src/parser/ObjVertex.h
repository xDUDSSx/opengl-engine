#pragma once

#include "pgr.h"

class ObjVertex {
public:
	glm::vec3 vertex;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;

	ObjVertex(glm::vec3 vertex);
};

inline ObjVertex::ObjVertex(glm::vec3 vertex) {
	this->vertex = vertex;
}
