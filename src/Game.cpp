#include "Game.h"

float Game::time = 0.0f;

std::unique_ptr<TextureManager> Game::textures = std::make_unique<TextureManager>();
std::unique_ptr<MeshManager> Game::meshes = std::make_unique<MeshManager>();

bool Game::drawDebugNormals = false;
float Game::normalDebugShaderMagnitude = 0.1f;

float Game::windStrength = 0.012f;
float Game::animSpeed = 60.0f;

bool Game::fogEnabled = false;
glm::vec3 Game::fogColor = glm::vec3(0.73, 0.85, 0.96);
float Game::fogNear = 50;
float Game::fogFar = 100;

bool Game::cameraCollision = true;

bool Game::disableLighting = false;
bool Game::disableNormalMapping = false;
