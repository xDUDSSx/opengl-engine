#include "Bridge.h"

void Bridge::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load model
	loadMesh("data/models/bridge_planks.obj", true, 4);
    loadMesh("data/models/bridge_rope.obj", true, 3);
    loadMesh("data/models/bridge_posts.obj", true);

    //Chocofur_wood_solid_10_diff.jpg

    const auto tSet = std::make_shared<TextureSet>();
    tSet->texture = std::make_shared<Texture>("data/textures/Chocofur_wood_solid_10_diff.jpg", "diffuse");
    this->textureSets.push_back(tSet);

    const auto tSet2 = std::make_shared<TextureSet>();
    tSet2->texture = std::make_shared<Texture>("data/textures/fabric_rope_a1_diffuse.jpg", "diffuse");
    tSet2->specularMap = std::make_shared<Texture>("data/textures/fabric_rope_a1_specular.jpg", "specular");
    tSet2->normalMap = std::make_shared<Texture>("data/textures/fabric_rope_a1_normal.jpg", "normal");
    this->textureSets.push_back(tSet2);

    addEmptyTextureSet();

	// Load textures
    //const auto tSet = std::make_shared<TextureSet>();
    //tSet->texture = std::make_shared<Texture>("data/textures/islands/Rock-cold_Albedo_light.jpg", "diffuse");
	//tSet->specularMap = std::make_shared<Texture>("data/textures/islands/Rock_Specular.jpg", "specular");
    //tSet->normalMap = std::make_shared<Texture>("data/textures/islands/Rock_Normal-s.jpg", "normal");
    //tSet->aoMap = std::make_shared<Texture>("data/textures/islands/Rock_AO.jpg", "ao");
    //this->textureSets.push_back(tSet);
}
