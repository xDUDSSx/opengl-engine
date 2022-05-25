#include "RotateEmpty.h"
#include "../../Game.h"

RotateEmpty::RotateEmpty(glm::vec3 axis)
	: RotateEmpty(axis, 1.0f)
{
	// Empty
}

RotateEmpty::RotateEmpty(glm::vec3 axis, float speed)
	: axis(axis)
	, speed(speed)
{
	// Empty	
}

void RotateEmpty::update() {
	Empty::update();
	transform.rot = axis * Game::time * Game::animSpeed * speed;
	//transform.rot.z = Game::time * Game::animSpeed;
}
