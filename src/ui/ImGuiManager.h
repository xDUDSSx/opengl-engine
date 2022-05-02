#pragma once

struct Settings;
class Entity;
class GameObject;

#include "../scene/Scene.h"

class ImGuiManager {
public:
	static bool show_demo_window;
	static bool show_another_window;

	static void init();
    static void draw(Scene& scene);
	static void dispose();

private:
	static void drawEntityInfo(Entity& entity);
};
