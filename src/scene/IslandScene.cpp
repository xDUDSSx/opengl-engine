#include "IslandScene.h"

#include "../entity/Airship.h"
#include "../entity/Camera.h"
#include "../entity/Capacitor.h"
#include "../entity/C4.h"
#include "../entity/Islands.h"
#include "../entity/Waterfall.h"
#include "../entity/animation/RotateEmpty.h"
#include "../entity/general/Empty.h"
#include "../entity/lights/CampfireGlow.h"
#include "../entity/lights/PointLight.h"
#include "../entity/lights/SpotLight.h"
#include "../entity/lights/SunLight.h"
#include "../entity/primitives/Billboard.h"
#include "../entity/primitives/Cube.h"
#include "../entity/primitives/Quad.h"

void createIslandScene(Scene* scene, Lighting* lighting, TextureManager* textures, PhongShader* shader, PhongShader* grassShader, Camera* airshipCamera)
{
    // Create lights
    /*
    PointLight* light1 = new PointLight();
    light1->create(shader);
    light1->transform.pos = glm::vec3(6, 4, 5);
    lighting->addLight(light1);
    scene->add(light1);

    PointLight* light2 = new PointLight();
    light2->create(shader);
    light2->transform.pos = glm::vec3(0, -2, 5);
    light2->color = glm::vec3(1.0, 0.0, 0.0);
    lighting->addLight(light2);
    scene->add(light2);

    PointLight* light3 = new PointLight();
    light3->create(shader);
    light3->transform.pos = glm::vec3(-3, -1.5, 0.5);
    lighting->addLight(light3);
    scene->add(light3);

    PointLight* light4 = new PointLight();
    light4->create(shader);
    light4->intensity = 2.0f;
    light4->radius = 15;
    light4->transform.pos = glm::vec3(2, 7, 3);
    lighting->addLight(light4);
    scene->add(light4);

    PointLight* light5 = new PointLight();
    light5->create(shader);
    light5->radius = 8;
    light5->transform.pos = glm::vec3(6, 7, 1);
    lighting->addLight(light5);
    scene->add(light5);

    PointLight* light6 = new PointLight();
    light6->create(shader);
    light6->radius = 20.0f;
    light6->transform.pos = glm::vec3(4, 10, 2);
    lighting->addLight(light6);
    scene->add(light6);
    */

    CampfireGlow* fireGlow = new CampfireGlow();
    fireGlow->create(shader);
    fireGlow->transform.pos = glm::vec3(8.27f, 35.22f, -1.51f);
    lighting->addLight(fireGlow);
    scene->add(fireGlow);

    SunLight* sun = new SunLight();
    sun->create(shader);
    sun->intensity = 0.8f;
    sun->color = glm::vec3(0.93, 0.98, 1.0);
    sun->direction = glm::vec3(-0.73, -0.21, -0.64);
    sun->transform.pos = glm::vec3(0, 0, 4);
    lighting->addLight(sun);
    scene->add(sun);

    SunLight* sun2 = new SunLight();
    sun2->create(shader);
    sun2->intensity = 0.12f;
    sun2->color = glm::vec3(0.69f, 0.91f, 1.0f);
    sun2->direction = glm::vec3(0.76, -0.12, 0.58);
    sun->transform.pos = glm::vec3(0, 0, 2);
	lighting->addLight(sun2);
    scene->add(sun2);

    /*
    SpotLight* spot = new SpotLight();
    spot->create(shader);
    spot->intensity = 0.4f;
    spot->transform.pos = glm::vec3(4, 3, 6);
    spot->direction = glm::vec3(3, -1.5, -6);
    lighting->addLight(spot);
    scene->add(spot);
    */

    // Create objects

    /*
    auto quad2 = new Quad();
    quad2->create(shader);
    quad2->transform.pos = glm::vec3(6, 7, -0.5);
    quad2->transform.scale = glm::vec3(3);
    quad2->materials[0]->shininess = 100;
    quad2->textureSets[0]->texture = textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-diffuse.jpg", "diffuse");
    quad2->textureSets[0]->specularMap = textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-specular2.jpg", "specular");
    quad2->textureSets[0]->aoMap = textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-ao.jpg", "ao");
    quad2->textureSets[0]->normalMap = textures->load("data/textures/stone_floor_4-2K/2K-stone_floor_4-normal.jpg", "normal");
    scene->add(quad2);
    */

    auto grass = new Quad();
    grass->create(grassShader);
    grass->setName("Grass 1");
    grass->opaque = false;
    grass->transform.pos = glm::vec3(-5.76f, 0.75f, -1.44f);
    grass->transform.rot = glm::vec3(-90, 45, 0);
    grass->transform.scale = glm::vec3(1.2f);
	grass->textureSets[0]->texture = textures->load("data/textures/grass.png", "diffuse");
    grass->textureSets[0]->texture->setClampToEdge();
    scene->add(grass);

    auto grass2 = new Quad();
    grass2->create(grassShader);
    grass2->setName("Grass 1");
    grass2->opaque = false;
    grass2->transform.pos = glm::vec3(-5.76f, 0.75f, -1.44f);
    grass2->transform.rot = glm::vec3(-90, -45, 0);
    grass2->transform.scale = glm::vec3(1.2f);
    grass2->textureSets[0]->texture = textures->load("data/textures/grass.png", "diffuse");
    grass2->textureSets[0]->texture->setClampToEdge();
    scene->add(grass2);

    //auto window1 = new Quad();
    //window1->setName("Window 1");
    //window1->create(shader);
    //window1->opaque = false;
    //window1->transform.scale = glm::vec3(3);
    //window1->transform.rot = glm::vec3(-90, 0, 0);
    //window1->transform.pos = glm::vec3(-3, 5, 0.5);
    //window1->textureSets[0]->texture = textures->load("data/textures/blending_transparent_window.png", "diffuse");
    //scene->add(window1);

    //auto window2 = new Quad();
    //window2->setName("Window 2");
    //window2->create(shader);
    //window2->opaque = false;
    //window2->transform.scale = glm::vec3(3);
    //window2->transform.rot = glm::vec3(-90, 0, 0);
    //window2->transform.pos = glm::vec3(-3, 8, 0.5);
    //window2->textureSets[0]->texture = textures->load("data/textures/blending_transparent_window.png", "diffuse");
    //scene->add(window2);

    auto fireEffect = new Quad();
    fireEffect->setName("Fire 1");
    fireEffect->create(shader);
    fireEffect->opaque = false;
    fireEffect->disableLighting = true;
    fireEffect->transform.scale = glm::vec3(3);
    fireEffect->transform.rot = glm::vec3(-90, 0, 0);
    fireEffect->transform.pos = glm::vec3(8.3, 35.2, -0.77);
    fireEffect->textureSets[0]->texture = textures->load("data/textures/fire.png", "diffuse");
    fireEffect->textureSets[0]->texture->setAnimated(1.0f / 5, 1.0f / 5, 0.7f);
    scene->add(fireEffect);

    auto fireEffect2 = new Quad();
    fireEffect2->setName("Fire 2");
    fireEffect2->create(shader);
    fireEffect2->opaque = false;
    fireEffect2->disableLighting = true;
    fireEffect2->transform.scale = glm::vec3(3);
    fireEffect2->transform.rot = glm::vec3(-90, 90, 0);
    fireEffect2->transform.pos = glm::vec3(8.3, 35.2, -0.77);
    fireEffect2->textureSets[0]->texture = textures->load("data/textures/fire.png", "diffuse");
    fireEffect2->textureSets[0]->texture->setAnimated(1.0f / 5, 1.0f / 5, 0.72f);
    scene->add(fireEffect2);

    //auto bill = new Billboard();
    //bill->create(shader);
    //bill->setName("Billboard");
    //bill->transform.pos = glm::vec3(2, 1, 2);
    //bill->textureSets[0]->texture = textures->load("data/textures/light.png", "diffuse");
    //scene->add(bill);

    /*
    auto cube = new Cube();
    cube->setName("Cube 1");
    cube->transform.pos = glm::vec3(0, -10, 0);
    cube->create(shader);
    scene->add(cube);

    auto cube2 = new Cube();
    cube2->transform.pos = glm::vec3(0, 3, 0);
    cube2->create(shader);
    cube2->setName("Cube 2");
    scene->add(cube, cube2);

    auto cube3 = new Cube();
    cube3->transform.pos = glm::vec3(0, 3, 1);
    cube3->create(shader);
    cube3->setName("Cube 3");
    scene->add(cube2, cube3);

    auto cube4 = new Cube();
    cube4->transform.pos = glm::vec3(3, 0, 2);
    cube4->create(shader);
    cube4->setName("Cube 4");
    scene->add(cube2, cube4);
    */

    // teapot = std::make_shared<Teapot>();
    // teapot->create(shader);
    // teapot->transform.pos = glm::vec3(8, 0, 0);

    /*
    auto capacitor = new Capacitor();
    capacitor->setName("Capacitor");
    capacitor->create(shader);
    capacitor->transform.pos = glm::vec3(0, 7, -1);
    capacitor->transform.scale = glm::vec3(3);
    scene->add(capacitor);
    */

    auto c4 = new C4();
    c4->setName("C4");
    c4->create(shader);
    c4->transform.pos = glm::vec3(5.1f, 35.71f, -1.640f);
    c4->transform.rot = glm::vec3(0, 0, 52.11f);
    c4->transform.scale = glm::vec3(0.35f);
    scene->add(c4);

#ifndef _DEBUG // To quicken loading
    const auto islands = new Islands();
    islands->create(shader);
    islands->setName("Islands");
    // islands->transform.pos = glm::vec3(-16.3f, 186.7f, -6.04f);
    islands->transform.pos = glm::vec3(0, 0, 0);
    islands->transform.scale = glm::vec3(6);
    islands->transform.rot = glm::vec3(0, 0, 90.0f);
    scene->add(islands);

    const auto house = new GameObject();
    house->create(shader);
    house->loadMesh("data/models/house.obj", true);
    auto tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/house/home_hatka_Base_Color.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/house/home_hatka_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/house/home_hatka_Normal_OpenGL.png", "normal");
    tSet->normalStrength = 0.5f;
    // tSet->aoMap = textures->load("data/textures/house/islands_bake_high_ao.jpg", "ao");
    house->textureSets.push_back(tSet);
    house->transform.rot = glm::vec3(0, 0, 90);
    house->transform.scale = glm::vec3(6);
    scene->add(house);

    // test = std::make_shared<TestSurface>();
    // test->create(shader);
    // test->transform.pos = glm::vec3(4, 10,-1);
    // test->transform.scale = glm::vec3(0.5f);

    auto airshipEmpty = new RotateEmpty(glm::vec3(0, 0, 1), 0.05f);
    airshipEmpty->create(shader);
    airshipEmpty->setName("Airship empty");
    airshipEmpty->transform.pos = glm::vec3(-2.8, 6.3, -3.71);
    scene->add(airshipEmpty);

    const auto airship = new Airship();
    airship->create(shader);
    airship->setName("Airship");
    airship->transform.pos = glm::vec3(83, 0, 22);
    airship->transform.rot = glm::vec3(0, 0, 90);
    airship->transform.scale = glm::vec3(4);

    scene->add(airshipEmpty, airship);
    scene->add(airship, airshipCamera);

    const auto tree_mango = new GameObject();
    tree_mango->create(shader);
    tree_mango->alphaCutoff = 0.5f; //Fix self inflicted blending issues

    tree_mango->loadMesh("data/models/tree_mango_trunk.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/tree_mango/tree_mangoBark_DIF.tga", "diffuse");
    tSet->specularMap = textures->load("data/textures/tree_mango/tree_mangoBark_SPC.tga", "specular");
    tSet->normalMap= textures->load("data/textures/tree_mango/tree_mangoBark_NMM.tga", "normal");
    tree_mango->textureSets.push_back(tSet);

    tree_mango->loadMesh("data/models/tree_mango_leaves.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/tree_mango/tree_mangoLeaves_DIF.tga", "diffuse");
    tSet->specularMap = textures->load("data/textures/tree_mango/tree_mangoLeaves_SPC.tga", "specular");
    tSet->normalMap = textures->load("data/textures/tree_mango/tree_mangoLeaves_NMM.tga", "normal");
    tree_mango->textureSets.push_back(tSet);

    tree_mango->transform.pos = glm::vec3(-18.12f, -4.47f, -2.82f);
    tree_mango->transform.rot = glm::vec3(0, 0, 31.44f);
    tree_mango->transform.scale = glm::vec3(6);
    scene->add(tree_mango);

    const auto tree_mango_2 = new GameObject();
    tree_mango_2->create(shader);
    tree_mango_2->alphaCutoff = 0.5f; // Fix self inflicted blending issues

	tree_mango_2->loadMesh("data/models/tree_mango_trunk.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/tree_mango/tree_mangoBark_DIF.tga", "diffuse");
    tSet->specularMap = textures->load("data/textures/tree_mango/tree_mangoBark_SPC.tga", "specular");
    tSet->normalMap = textures->load("data/textures/tree_mango/tree_mangoBark_NMM.tga", "normal");
    tree_mango_2->textureSets.push_back(tSet);

    tree_mango_2->loadMesh("data/models/tree_mango_leaves.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/tree_mango/tree_mangoLeaves_DIF.tga", "diffuse");
    tSet->specularMap = textures->load("data/textures/tree_mango/tree_mangoLeaves_SPC.tga", "specular");
    tSet->normalMap = textures->load("data/textures/tree_mango/tree_mangoLeaves_NMM.tga", "normal");
    tree_mango_2->textureSets.push_back(tSet);

    tree_mango_2->transform.pos = glm::vec3(-22.45f, -16.25f, 2.26f);
    tree_mango_2->transform.rot = glm::vec3(0, 0, -99.66f);
    tree_mango_2->transform.scale = glm::vec3(6);
    scene->add(tree_mango_2);

    const auto tree_hornbeam = new GameObject();
    tree_hornbeam->create(shader);
    tree_hornbeam->alphaCutoff = 0.5f; // Fix self inflicted blending issues

    tree_hornbeam->loadMesh("data/models/tree_hornbeam_trunk.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/tree_hornbeam/WC_Hornbeam_Bark.jpg", "diffuse");
    tree_hornbeam->textureSets.push_back(tSet);

    tree_hornbeam->loadMesh("data/models/tree_hornbeam_leaves.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/tree_hornbeam/WC_Hornbeam_Leaf.tga", "diffuse");
    tree_hornbeam->textureSets.push_back(tSet);

    tree_hornbeam->transform.pos = glm::vec3(-2.58f, 32.36f, -2.31f);
    tree_hornbeam->transform.rot = glm::vec3(0, 0, -28.23f);
    tree_hornbeam->transform.scale = glm::vec3(6);
    scene->add(tree_hornbeam);
#endif

    const auto waterfall_rock_1 = new GameObject();
    waterfall_rock_1->create(shader);

    waterfall_rock_1->loadMesh("data/models/waterfall_rock1.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/Large_Rock_01_Diffuse.jpg", "diffuse");
    tSet->normalMap = textures->load("data/textures/Large_Rock_01_Normal.jpg", "normal");
    waterfall_rock_1->textureSets.push_back(tSet);
    
    waterfall_rock_1->transform.rot = glm::vec3(0, 0, 90);
    waterfall_rock_1->transform.scale = glm::vec3(6);
    scene->add(waterfall_rock_1);

    const auto waterfall_rock_2 = new GameObject();
    waterfall_rock_2->create(shader);

    waterfall_rock_2->loadMesh("data/models/waterfall_rock_arch_1.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/campfire/rock_2.jpg", "diffuse");
    waterfall_rock_2->textureSets.push_back(tSet);

    waterfall_rock_2->transform.rot = glm::vec3(0, 0, 90);
    waterfall_rock_2->transform.scale = glm::vec3(6);
    scene->add(waterfall_rock_2);

    const auto waterfall_rock_3 = new GameObject();
    waterfall_rock_3->create(shader);

    waterfall_rock_3->loadMesh("data/models/waterfall_rock3.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/rock3/Large_Rock_04_Diffuse.jpg", "diffuse");
    tSet->normalMap = textures->load("data/textures/rock3/Large_Rock_04_Normal.jpg", "normal");
    waterfall_rock_3->textureSets.push_back(tSet);

    waterfall_rock_3->transform.rot = glm::vec3(0, 0, 90);
    waterfall_rock_3->transform.scale = glm::vec3(6);
    scene->add(waterfall_rock_3);

    const auto waterfall_rock_4 = new GameObject();
    waterfall_rock_4->create(shader);

    waterfall_rock_4->loadMesh("data/models/waterfall_rock_arch_2.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/campfire/rock_1.jpg", "diffuse");
    waterfall_rock_4->textureSets.push_back(tSet);

    waterfall_rock_4->transform.rot = glm::vec3(0, 0, 90);
    waterfall_rock_4->transform.scale = glm::vec3(6);
    scene->add(waterfall_rock_4);

    auto waterfall = new Waterfall();
    waterfall->create(shader);
    waterfall->setName("Waterfall");
    scene->add(waterfall);

    const auto houseFlowers = new GameObject();
    houseFlowers->create(grassShader);
    houseFlowers->loadMesh("data/models/flowers.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/house/grass_05.tga", "diffuse");
    tSet->texture->setClampToEdge();
    houseFlowers->textureSets.push_back(tSet);
    houseFlowers->transform.rot = glm::vec3(0, 0, 90);
    houseFlowers->transform.scale = glm::vec3(6);
    scene->add(houseFlowers);

    const auto fences = new GameObject();
    fences->create(shader);

    fences->loadMesh("data/models/fences_planks.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/fences/planks.jpg", "diffuse");
    tSet->normalMap = textures->load("data/textures/fences/planks_NRM.jpg", "normal");
    fences->textureSets.push_back(tSet);

    fences->loadMesh("data/models/fences_logs.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/fences/logs.jpg", "diffuse");
    tSet->normalMap = textures->load("data/textures/fences/logs_NRM.jpg", "normal");
    fences->textureSets.push_back(tSet);

    fences->loadMesh("data/models/fences_logends.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/fences/logends.jpg", "diffuse");
    tSet->normalMap = textures->load("data/textures/fences/logends_NRM.jpg", "normal");
    fences->textureSets.push_back(tSet);

    fences->transform.rot = glm::vec3(0, 0, 90);
    fences->transform.scale = glm::vec3(6);
    scene->add(fences);

    const auto bridge_new = new GameObject();
    bridge_new->create(shader);

    bridge_new->loadMesh("data/models/bridge_planks.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/bridge/planks_2K_Diffuse.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/bridge/planks_2K_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/bridge/planks_2K_Normal.png", "normal");
    tSet->aoMap = textures->load("data/textures/bridge/planks_2K_AO.png", "ao");
    bridge_new->textureSets.push_back(tSet);

    bridge_new->loadMesh("data/models/bridge_rope.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/bridge/rope_2K_Diffuse.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/bridge/rope_2K_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/bridge/rope_2K_Normal.png", "normal");
    tSet->aoMap = textures->load("data/textures/bridge/rope_2K_AO.png", "ao");
    bridge_new->textureSets.push_back(tSet);

    bridge_new->loadMesh("data/models/bridge_pole.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/bridge/pole_2K_Diffuse.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/bridge/pole_2K_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/bridge/pole_2K_Normal.png", "normal");
    tSet->aoMap = textures->load("data/textures/bridge/pole_2K_AO.png", "ao");
    bridge_new->textureSets.push_back(tSet);

    bridge_new->transform.rot = glm::vec3(0, 0, 90);
    bridge_new->transform.scale = glm::vec3(6);
    scene->add(bridge_new);

    const auto campfire = new GameObject();
    campfire->create(shader);

    campfire->addEmptyMaterial();
    campfire->materials[0]->diffuse = glm::vec3(0.37f, 0.19f, 0.07f);

    campfire->loadMesh("data/models/campfire_bark.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/campfire/bark_1.jpg", "diffuse");
    campfire->textureSets.push_back(tSet);

    campfire->loadMesh("data/models/campfire_stone1.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/campfire/rock_1.jpg", "diffuse");
    campfire->textureSets.push_back(tSet);

    campfire->loadMesh("data/models/campfire_stone2.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/campfire/rock_2.jpg", "diffuse");
    campfire->textureSets.push_back(tSet);

    campfire->transform.rot = glm::vec3(0, 0, 90);
    campfire->transform.scale = glm::vec3(6);
    scene->add(campfire);

    const auto bench1 = new GameObject();
    bench1->create(shader);

    bench1->loadMesh("data/models/bench.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/house/branch_Base_Color.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/house/branch_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/house/branch_Normal_OpenGL.png", "normal");
    tSet->normalStrength = 0.45f;
	bench1->textureSets.push_back(tSet);

    bench1->transform.pos = glm::vec3(0.6f, -20.868, 3.150);
    bench1->transform.rot = glm::vec3(0, 0, 93.5f);
    bench1->transform.scale = glm::vec3(6);
    scene->add(bench1);

    const auto bench2 = new GameObject();
    bench2->create(shader);

    bench2->loadMesh("data/models/bench.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/house/branch_Base_Color.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/house/branch_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/house/branch_Normal_OpenGL.png", "normal");
    tSet->normalStrength = 0.45f;
    bench2->textureSets.push_back(tSet);

    bench2->transform.pos = glm::vec3(-16, -23.74f, 2.6f);
    bench2->transform.rot = glm::vec3(0, 0, 295.74f);
    bench2->transform.scale = glm::vec3(6);
    scene->add(bench2);

    const auto bench3 = new GameObject();
    bench3->create(shader);

    bench3->loadMesh("data/models/bench.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/house/branch_Base_Color.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/house/branch_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/house/branch_Normal_OpenGL.png", "normal");
    tSet->normalStrength = 0.45f;
    bench3->textureSets.push_back(tSet);

    bench3->transform.pos = glm::vec3(-15.13f, -2.1f, -2.27f);
    bench3->transform.rot = glm::vec3(-2.16f, -5.55f, -123);
    bench3->transform.scale = glm::vec3(6);
    scene->add(bench3);

    const auto bench4 = new GameObject();
    bench4->create(shader);

    bench4->loadMesh("data/models/bench.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/house/branch_Base_Color.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/house/branch_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/house/branch_Normal_OpenGL.png", "normal");
    tSet->normalStrength = 0.45f;
    bench4->textureSets.push_back(tSet);

    bench4->transform.pos = glm::vec3(4.94f, 35.28f, -1.67f);
    bench4->transform.rot = glm::vec3(0, 0, 90);
    bench4->transform.scale = glm::vec3(6);
    scene->add(bench4);

    const auto bench5 = new GameObject();
    bench5->create(shader);

    bench5->loadMesh("data/models/bench.obj", true);
    tSet = std::make_shared<TextureSet>();
    tSet->texture = textures->load("data/textures/house/branch_Base_Color.png", "diffuse");
    tSet->specularMap = textures->load("data/textures/house/branch_Specular.png", "specular");
    tSet->normalMap = textures->load("data/textures/house/branch_Normal_OpenGL.png", "normal");
    tSet->normalStrength = 0.45f;
    bench5->textureSets.push_back(tSet);

    bench5->transform.pos = glm::vec3(7.28f, 32.08f, -1.64f);
    bench5->transform.rot = glm::vec3(0, 0, 160.2f);
    bench5->transform.scale = glm::vec3(6);
    scene->add(bench5);
}