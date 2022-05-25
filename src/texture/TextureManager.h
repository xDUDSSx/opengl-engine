#pragma once
#include <unordered_map>

#include "Texture.h"

/**
 * \brief Manager responsible for texture caching.
 */
class TextureManager {
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

public:
	Texture* load(const char* path);
	Texture* load(const char* path, std::string type);
	Texture* load(const char* path, std::string type, GLenum target);

	void dispose();
};
