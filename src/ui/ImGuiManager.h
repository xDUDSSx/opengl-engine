#pragma once

class Entity;
class GameObject;

class ImGuiManager {
public:
    static bool show_demo_window;
    static bool show_another_window;

    static void init();
    static void draw(GameObject& test);
    static void dispose();

private:
    static void drawEntityInfo(Entity& entity);
};
