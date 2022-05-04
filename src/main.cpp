#include "pgr.h"
#include <iostream>

#include "Game.h"
#include "imgui_impl_glut.h"
#include "InputManager.h"
#include "Lighting.h"
#include "Skybox.h"
#include "entity/Airship.h"
#include "entity/Bridge.h"

#include "texture/Texture.h"
#include "texture/Cubemap.h"

#include "entity/Camera.h"
#include "entity/Capacitor.h"
#include "entity/C4.h"
#include "entity/Islands.h"
#include "entity/TestSurface.h"
#include "entity/animation/RotateEmpty.h"
#include "entity/general/Empty.h"
#include "entity/lights/PointLight.h"
#include "entity/lights/SpotLight.h"
#include "entity/lights/SunLight.h"
#include "entity/primitives/Cube.h"
#include "entity/primitives/Quad.h"
#include "entity/primitives/Teapot.h"
#include "scene/Scene.h"
#include "shader/GrassShader.h"

#include "shader/PhongShader.h"
#include "shader/NormalDebugShader.h"
#include "shader/SkyboxShader.h"
#include "ui/ImGuiManager.h"

int winWidth = 1200;
int winHeight = 800;
std::string winTitle = "Floating islands";
int fps = 1000 / 144;

int mouseX = 0;
int mouseY = 0;
int mouseDx = 0;
int mouseDy = 0;

std::shared_ptr<Scene> scene;

std::shared_ptr<Camera> camera1;
std::shared_ptr<Camera> camera2;
std::shared_ptr<Camera> airshipCamera;
std::shared_ptr<Camera> activeCamera;

std::shared_ptr<PhongShader> shader;
std::shared_ptr<NormalDebugShader> normalDebugShader;
std::shared_ptr<SkyboxShader> skyboxShader;
std::shared_ptr<GrassShader> grassShader;

std::shared_ptr<Lighting> lighting;
std::shared_ptr<Cubemap> cubemap;
std::shared_ptr<Skybox> skybox;

std::shared_ptr<Quad> quad;
std::shared_ptr<Quad> quad2;
std::shared_ptr<Cube> cube;
std::shared_ptr<Teapot> teapot;
std::shared_ptr<TestSurface> test;

bool ignoreMouseEvent = false;

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilMask(0x00);
	glDepthMask(GL_FALSE);
	skyboxShader->use();
	skybox->render(*skyboxShader, *activeCamera);
	glDepthMask(GL_TRUE);

	glStencilMask(0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	shader->use();
	lighting->setUniforms(*shader);

	grassShader->use();
	lighting->setUniforms(*grassShader);

	grassShader->setUniforms(); // Update time of grass shader

	scene->render(*activeCamera);
	if (Game::drawDebugNormals) {
		normalDebugShader->use();
		normalDebugShader->setUniforms();
		scene->render(normalDebugShader.get(), *activeCamera);
	}

	glStencilMask(0x00);

	ImGuiManager::draw(*scene, *activeCamera);

	glutSwapBuffers();
}

void update(int delta)
{
	Game::time = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME);

	activeCamera->keyboard(
        InputManager::keyMap[InputManager::IM_KEY_w],
        InputManager::keyMap[InputManager::IM_KEY_s],
        InputManager::keyMap[InputManager::IM_KEY_a],
        InputManager::keyMap[InputManager::IM_KEY_d],
		InputManager::isShiftDown()
    );
	
	scene->update();

	glutTimerFunc(fps, update, 0);
	glutPostRedisplay();
}

void initUI()
{
	ImGuiManager::init();
}

void init()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearStencil(0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_STENCIL_TEST);
	//glEnable(GL_CULL_FACE);

	initUI();

	scene = std::make_shared<Scene>();

	// Create shaders
	shader = std::make_shared<PhongShader>("data/shaders/phongVert.glsl", "data/shaders/phongFrag.glsl");

	std::string geoShader = "data/shaders/normalDebugGeo.glsl";
	normalDebugShader = std::make_shared<NormalDebugShader>("data/shaders/normalDebugVert.glsl", "data/shaders/normalDebugFrag.glsl", &geoShader);

	skyboxShader = std::make_shared<SkyboxShader>("data/shaders/skyboxVert.glsl", "data/shaders/skyboxFrag.glsl");

	grassShader = std::make_shared<GrassShader>("data/shaders/grassVert.glsl", "data/shaders/phongFrag.glsl");

	// Create cameras
    camera1 = std::make_shared<Camera>(winWidth, winHeight, glm::vec3(0, 0, 0));
    camera1->setName("Camera 1");
	camera1->create(shader.get());
    scene->add(camera1.get());

    camera2 = std::make_shared<Camera>(winWidth, winHeight, glm::vec3(0, 5, 0));
    camera2->setName("Camera 2");
	camera2->create(shader.get());

	airshipCamera = std::make_shared<Camera>(winWidth, winHeight, glm::vec3(0, 0, 0));
    airshipCamera->setName("Camera 3 (Airship)");
	airshipCamera->rotationX = -90;
	airshipCamera->create(shader.get());

    activeCamera = camera1;

	// Create lights
	lighting = std::make_shared<Lighting>();

	PointLight* light1 = new PointLight();
	light1->transform.pos = glm::vec3(6, 4, 5);
	lighting->addLight(light1);
	scene->add(light1);

	PointLight* light2 = new PointLight();
	light2->transform.pos = glm::vec3(0, -2, 5);
	light2->color = glm::vec3(1.0, 0.0, 0.0);
	lighting->addLight(light2);
    scene->add(light2); 

	PointLight* light3 = new PointLight();
	light3->transform.pos = glm::vec3(-3, -1.5, 0.5);
	lighting->addLight(light3);
    scene->add(light3); 

	PointLight* light4 = new PointLight();
	light4->intensity = 2.0f;
	light4->radius = 15;
	light4->transform.pos = glm::vec3(2, 7, 3);
	lighting->addLight(light4);
    scene->add(light4); 

	PointLight* light5 = new PointLight();
	light4->radius = 8;
	light5->transform.pos = glm::vec3(6, 7, 1);
	lighting->addLight(light5);
    scene->add(light5); 

	PointLight* light6 = new PointLight();
	light6->radius = 20.0f;
	light6->transform.pos = glm::vec3(4, 10, 2);
	lighting->addLight(light6);
    scene->add(light6); 

	SunLight* sun = new SunLight();
	sun->color = glm::vec3(0.93, 0.98, 1.0);
	sun->direction = glm::vec3(0.5, 0.5, -1);
	lighting->addLight(sun);
    scene->add(sun); 

	SpotLight* spot = new SpotLight();
	spot->intensity = 0.4f;
	spot->transform.pos = glm::vec3(4, 3, 6);
	spot->direction = glm::vec3(3, -1.5, -6);
	lighting->addLight(spot);
    scene->add(spot); 

	// Create objects
	//quad = std::make_shared<Quad>();
	//quad->create(shader.get());
	//quad->transform.pos = glm::vec3(0, -10, -1);
	//quad->transform.scale = glm::vec3(100);
	//scene->add(quad.get()); 

	quad2 = std::make_shared<Quad>();
	quad2->create(shader.get());
	quad2->transform.pos = glm::vec3(6, 7, -0.5);
	quad2->transform.scale = glm::vec3(3);
    quad2->materials[0]->shininess = 100;
    quad2->textureSets[0]->texture = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-diffuse.jpg", "diffuse");
    quad2->textureSets[0]->specularMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-specular2.jpg", "specular");
    quad2->textureSets[0]->aoMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-ao.jpg", "ao");
    quad2->textureSets[0]->normalMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-normal.jpg", "normal");
	scene->add(quad2.get());

	auto grass = new Quad();
	grass->create(grassShader.get());
    grass->setName("Grass 1");
	grass->opaque = false;
	grass->transform.scale = glm::vec3(3);
	grass->transform.rot = glm::vec3(-90, 0, 0);
	grass->transform.pos = glm::vec3(-3, 3, 0.5);
    grass->textureSets[0]->texture = std::make_shared<Texture>("data/textures/grass.png", "diffuse");
    grass->textureSets[0]->texture->setClampToEdge();
	scene->add(grass);

	auto window1 = new Quad();
    window1->setName("Window 1");
	window1->create(shader.get());
	window1->opaque = false;
	window1->transform.scale = glm::vec3(3);
	window1->transform.rot = glm::vec3(-90, 0, 0);
	window1->transform.pos = glm::vec3(-3, 5, 0.5);
	window1->textureSets[0]->texture = std::make_shared<Texture>("data/textures/blending_transparent_window.png", "diffuse");
	scene->add(window1);

	auto window2 = new Quad();
    window2->setName("Window 2");
	window2->create(shader.get());
	window2->opaque = false;
	window2->transform.scale = glm::vec3(3);
	window2->transform.rot = glm::vec3(-90, 0, 0);
	window2->transform.pos = glm::vec3(-3, 8, 0.5);
    window2->textureSets[0]->texture = std::make_shared<Texture>("data/textures/blending_transparent_window.png", "diffuse");
	scene->add(window2);

	cube = std::make_shared<Cube>();
    cube->setName("Cube 1");
	cube->transform.pos = glm::vec3(0, -10, 0);
	cube->create(shader.get());
	scene->add(cube.get());

	auto cube2 = new Cube();
	cube2->transform.pos = glm::vec3(0, 3, 0);
	cube2->create(shader.get());
    cube2->setName("Cube 2");
	scene->add(cube.get(), cube2);
	
	auto cube3 = new Cube();
    cube3->transform.pos = glm::vec3(0, 3, 1);
    cube3->create(shader.get());
    cube3->setName("Cube 3");
    scene->add(cube2, cube3);

	auto cube4 = new Cube();
    cube4->transform.pos = glm::vec3(3, 0, 2);
    cube4->create(shader.get());
    cube4->setName("Cube 4");
    scene->add(cube2, cube4);

	//teapot = std::make_shared<Teapot>();
	//teapot->create(shader.get());
	//teapot->transform.pos = glm::vec3(8, 0, 0);

	auto capacitor = new Capacitor();
    capacitor->setName("Capacitor");
	capacitor->create(shader.get());
	capacitor->transform.pos = glm::vec3(0, 7, -1);
	capacitor->transform.scale = glm::vec3(3);
    scene->add(capacitor);

	auto c4 = new C4();
    c4->setName("C4");
	c4->create(shader.get());
	c4->transform.pos = glm::vec3(0, 4, 0);
	c4->transform.scale = glm::vec3(1);
    scene->add(c4);

	const auto islands = new Islands();
	islands->create(shader.get());
    islands->setName("Islands");
	islands->transform.pos = glm::vec3(-16.3f, 186.7f, -6.04f);
	islands->transform.scale = glm::vec3(6);
    islands->transform.rot= glm::vec3(0, 0, 90.0f);
	scene->add(islands);

	const auto bridge = new Bridge();
    bridge->create(shader.get());
    bridge->setName("Bridge");
    bridge->transform.pos = glm::vec3(13.99f, 50.8f, -2.21);
    bridge->transform.scale = glm::vec3(0.85);
    bridge->transform.rot = glm::vec3(-3.750, 0, 84.95f);
    scene->add(bridge);

	//test = std::make_shared<TestSurface>();
	//test->create(shader.get());
	//test->transform.pos = glm::vec3(4, 10,-1);
	//test->transform.scale = glm::vec3(0.5f);

	auto airshipEmpty = new RotateEmpty(glm::vec3(0, 0, 1), 0.05f);
    airshipEmpty->create(shader.get());
    airshipEmpty->setName("Airship empty");
	airshipEmpty->transform.pos = glm::vec3(6.66, 36.8, 0);
    scene->add(airshipEmpty);

	const auto airship = new Airship();
    airship->create(shader.get());
    airship->setName("Airship");
    airship->transform.pos = glm::vec3(83, 0, 16.6);
    airship->transform.rot = glm::vec3(0, 0, 90);
    airship->transform.scale = glm::vec3(4);

    scene->add(airshipEmpty, airship);
    scene->add(airship, airshipCamera.get());

	auto cameraEmpty = new Empty();
    cameraEmpty->create(shader.get());
    cameraEmpty->transform.pos = glm::vec3(-5, -5, 0);
    scene->add(cameraEmpty);
    scene->add(cameraEmpty, camera2.get());

	// Create skybox
	std::vector<std::string> cubemapTextures;
	cubemapTextures.push_back("data/textures/skybox_front.png");
	cubemapTextures.push_back("data/textures/skybox_back.png");
	cubemapTextures.push_back("data/textures/skybox_left.png");
	cubemapTextures.push_back("data/textures/skybox_right.png");
	cubemapTextures.push_back("data/textures/skybox_top.png");
	cubemapTextures.push_back("data/textures/skybox_bottom.png");
	cubemap = std::make_shared<Cubemap>(cubemapTextures);

	skybox = std::make_shared<Skybox>(cubemap);
	skybox->create(*skyboxShader);
}

void reshape(int newWidth, int newHeight) {
	winWidth = newWidth;
	winHeight = newHeight;
	glViewport(0, 0, winWidth, winHeight);
	activeCamera->size(winWidth, winHeight);
	ImGui_ImplGLUT_ReshapeFunc(newWidth, newHeight);
};

/**
 * \brief Handle the key pressed event.
 * Called whenever a key on the keyboard was pressed. The key is given by the "keyPressed"
 * parameter, which is an ASCII character. It's often a good idea to have the escape key (ASCII value 27)
 * to call glutLeaveMainLoop() to exit the program.
 * \param keyPressed ASCII code of the key
 * \param mouseX mouse (cursor) X position
 * \param mouseY mouse (cursor) Y position
 */
void keyboardCb(unsigned char keyPressed, int mouseX, int mouseY) {
    keyPressed = tolower(keyPressed); //Fixes stuff like shift causing problems with uppercase letters

	switch (keyPressed) {
		case 27: // escape
			#ifndef __APPLE__
				glutLeaveMainLoop();
			#else
				exit(0);
			#endif
			break;
		case '1':
			activeCamera = camera1;
			activeCamera->size(winWidth, winHeight);
			break;
		case '2':
			activeCamera = camera2;
			activeCamera->size(winWidth, winHeight);
			break;
        case '3':
            activeCamera = airshipCamera;
            activeCamera->size(winWidth, winHeight);
            break;
		case ',': 
			{
	            Entity* e = scene->getSelectedEntity();
	            if (e != nullptr) {
	                activeCamera->pivot = e->worldTransform.pos;
	            }
            }
            break;
		case 'f':
            activeCamera->toggleFpsMode(); 
			break;
	}
	ImGui_ImplGLUT_KeyboardFunc(keyPressed, mouseX, mouseY);
	InputManager::keyMap[InputManager::glutKeyToImKey(keyPressed)] = true;
}

/**
 * Called whenever a key on the keyboard was released. The key is given by
 * the "keyReleased" parameter, which is in ASCII.
 * \brief Handle the key released event.
 * \param keyReleased ASCII code of the released key
 * \param mouseX mouse (cursor) X position
 * \param mouseY mouse (cursor) Y position
 */
void keyboardUpCb(unsigned char keyReleased, int mouseX, int mouseY) {
    keyReleased = tolower(keyReleased); // Fixes stuff like shift causing problems with uppercase letters
	ImGui_ImplGLUT_KeyboardUpFunc(keyReleased, mouseX, mouseY);
	InputManager::keyMap[InputManager::glutKeyToImKey(keyReleased)] = false;
}

//
/**
 * \brief Handle the non-ASCII key pressed event (such as arrows of F1).
 *  The special keyboard callback is triggered when keyboard function (Fx) or directional
 *  keys are pressed.
 * \param specKeyPressed int value of a predefined glut constant such as GLUT_KEY_UP
 * \param mouseX mouse (cursor) X position
 * \param mouseY mouse (cursor) Y position
 */
void specialKeyboardCb(int specKeyPressed, int mouseX, int mouseY) {
	switch (specKeyPressed) {
	case GLUT_KEY_F1:
			Game::drawDebugNormals = !Game::drawDebugNormals;
			break;
	}
	ImGui_ImplGLUT_SpecialFunc(specKeyPressed, mouseX, mouseY);
	InputManager::keyMap[InputManager::glutSpecialKeyToImKey(specKeyPressed)] = true;
}

void specialKeyboardUpCb(int specKeyReleased, int mouseX, int mouseY) {
	ImGui_ImplGLUT_SpecialUpFunc(specKeyReleased, mouseX, mouseY);
	InputManager::keyMap[InputManager::glutSpecialKeyToImKey(specKeyReleased)] = false;
}

/**
 * \brief React to mouse button press and release (mouse click).
 * When the user presses and releases mouse buttons in the window, each press
 * and each release generates a mouse callback (including release after dragging).
 *
 * \param button button code (GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON)
 * \param state GLUT_DOWN when pressed, GLUT_UP when released
 * \param x mouse (cursor) X position
 * \param y mouse (cursor) Y position
 */
void mouseClicked(int button, int state, int x, int y) {
	mouseX = x;
	mouseY = y;
	ImGui_ImplGLUT_MouseFunc(button, state, x, y);
	InputManager::mouseMap[InputManager::glutMouseButtonToImMouseButton(button)] = (state == GLUT_DOWN);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		uint8_t id = 0;
		glReadPixels(x, winHeight - y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &id);
		std::cout << "Clicked on id: " << unsigned(id) << std::endl;
		scene->select(id);
	}
}

void mouseWheel(int wheel, int dir, int x, int y)
{
	mouseX = x;
	mouseY = y;
	ImGui_ImplGLUT_MouseWheelFunc(wheel, dir, x, y);
	if (!ImGui::GetIO().WantCaptureMouse) {
		activeCamera->mouseWheel(dir, 1);
	}
}

/**
 * \brief Handle mouse dragging (mouse move with any button pressed).
 *        This event follows the glutMouseFunc(mouseCb) event.
 * \param x mouse (cursor) X position
 * \param y mouse (cursor) Y position
 */
void mouseDragged(int x, int y) {
	mouseDx = x - mouseX;
	mouseDy = y - mouseY;
	mouseX = x;
	mouseY = y;
	ImGui_ImplGLUT_MotionFunc(x, y);

	if (!ImGui::GetIO().WantCaptureMouse) {
		activeCamera->mouseDrag(mouseDx, mouseDy,
			InputManager::mouseMap[InputManager::IM_MOUSE_BUTTON_LEFT],
			InputManager::mouseMap[InputManager::IM_MOUSE_BUTTON_MIDDLE]
		);
	}
    glutPostRedisplay();
}

/**
 * \brief Handle mouse movement over the window (with no button pressed).
 * \param x mouse (cursor) X position
 * \param y mouse (cursor) Y position
 */
void mouseMoved(int x, int y) {
	mouseDx = x - mouseX;
    mouseDy = y - mouseY;
	mouseX = x;
	mouseY = y;
	ImGui_ImplGLUT_MotionFunc(x, y);
    if (!ImGui::GetIO().WantCaptureMouse) {
        activeCamera->mouseMoved(mouseDx, mouseDy);
    	if (activeCamera->fpsMode) {
            //int border = 3;
            //if (x < border) {
            //    glutWarpPointer(winWidth - border, y);    
            //}
            //if (x > winWidth - border) {
            //    glutWarpPointer(border, y);
            //}

            //int centerX = winWidth / 2;
            //int centerY = winHeight / 2;
            //if (x != centerX || y != centerY) {
            //    glutWarpPointer(centerX, centerY);
            //}
        }
    }
    glutPostRedisplay();
}

/**
 * \brief Delete all OpenGL objects and application data.
 */
void dispose(void) {

	// cleanUpObjects();

	// delete buffers
	// cleanupModels();

	// delete shaders
	// cleanupShaderPrograms();

	skybox->dispose();

	scene->dispose();

	shader->dispose();
	skyboxShader->dispose();
	normalDebugShader->dispose();

	ImGuiManager::dispose();
}

/**
 * \brief Entry point of the application.
 * \param argc number of command line arguments
 * \param argv array with argument strings
 * \return 0 if OK, <> elsewhere
 */
int main(int argc, char** argv)
{
	// initialize the GLUT library (windowing system)
	glutInit(&argc, argv);

	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, 4);

	// for each window
	{
		//   initial window size + title
		glutInitWindowSize(winWidth, winHeight);
		glutCreateWindow(winTitle.c_str());

		// Callbacks - use only those you need
		glutDisplayFunc(render);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboardCb);
		glutKeyboardUpFunc(keyboardUpCb);
		glutSpecialFunc(specialKeyboardCb);     // key pressed
		glutSpecialUpFunc(specialKeyboardUpCb); // key released
		glutMouseFunc(mouseClicked);
		glutMotionFunc(mouseDragged);
		glutPassiveMotionFunc(mouseMoved);
		glutMouseWheelFunc(mouseWheel);
		glutTimerFunc(fps, update, 0);
	}
	// end for each window

	// initialize PGR framework (GL, DevIl, etc.)
	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");

	// init your stuff - shaders & program, buffers, locations, state of the application
	init();

	// handle window close by the user
	glutCloseFunc(dispose);

	// Infinite loop handling the events
	glutMainLoop();

	// code after glutLeaveMainLoop()
	// cleanup

	return 0;
}
