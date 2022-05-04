#include "Game.h"

float Game::time = 0.0f;

bool Game::drawDebugNormals = false;
float Game::normalDebugShaderMagnitude = 0.1f;

float Game::windStrength = 0.1f;
float Game::animSpeed = 60.0f;

bool Game::fogEnabled = false;
glm::vec3 Game::fogColor = glm::vec3(0.73, 0.85, 0.96);
float Game::fogNear = 50;
float Game::fogFar = 100;