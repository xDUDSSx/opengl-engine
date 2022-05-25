#include "TextureManager.h"

Texture* TextureManager::load(const char* path) {
	return load(path, "texture");
}

Texture* TextureManager::load(const char* path, std::string type) {
	return load(path, type, GL_TEXTURE_2D);
}

Texture* TextureManager::load(const char* path, std::string type, GLenum target) {
	std::string textureKey = (path + std::string("#") + type + "#" + std::to_string(target));
	if (textures.find(textureKey) == textures.end()) {
		// Texture is not registered
		auto texture = std::make_shared<Texture>(path, type, target);
		textures[textureKey] = texture;
		printf("[TEXTURE] Registered texture '%s'\n", textureKey.c_str());
	}
	return textures[textureKey].get();
}

void TextureManager::dispose() {
	for (auto& e : textures) {
		e.second->dispose();
	}
}
