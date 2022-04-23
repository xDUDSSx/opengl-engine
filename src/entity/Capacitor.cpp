#include "Capacitor.h"

#include "../parser/ObjParser.h"

void Capacitor::render(std::shared_ptr<Camera> camera)
{
    GameObject::render(camera);
}

void Capacitor::update()
{
    GameObject::update();
}

void Capacitor::create(std::shared_ptr<PhongShader> shader)
{
    GameObject::create(shader);

    material->shininess = 24;

    // Load model
    ObjParser parser("data/models/capacitor1.obj");
    int triangles = parser.getTriangleCount();
    std::vector<float> vbo;
    parser.getDrawArraysGeo(vbo);
    Mesh* g = new Mesh(vbo.data(), vbo.size(), triangles, *this->shader);
    this->mesh = std::shared_ptr<Mesh>(g);

    // Load texture
    //this->texture = std::make_shared<Texture>("data/textures/capacitor/capacitor_base_color.png", "diffuse");
    // this->specularMap = std::make_shared<Texture>("data/textures/container2_specular.png", "specular");
    this->normalMap = std::make_shared<Texture>("data/textures/capacitor/capacitor_base_normal.png", "normal");
}
