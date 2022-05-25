#pragma once
#include <unordered_map>

#include "Mesh.h"

/**
 * \brief Manager responsible for mesh caching.
 */
class MeshManager {
private:
	std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;

public:
	Mesh* load(const char* path, bool arraysOrElements, float uvScale, PhongShader& shader);

	void dispose();
};
