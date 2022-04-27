#include "pgr.h"
#include "AntTweakBar.h"
#include <iostream>

#include "Game.h"
#include "InputManager.h"
#include "Lighting.h"
#include "Skybox.h"

#include "texture/Texture.h"
#include "texture/Cubemap.h"

#include "entity/Camera.h"
#include "entity/Capacitor.h"
#include "entity/C4.h"
#include "entity/TestSurface.h"
#include "entity/lights/PointLight.h"
#include "entity/lights/SpotLight.h"
#include "entity/lights/SunLight.h"
#include "entity/primitives/Cube.h"
#include "entity/primitives/Quad.h"
#include "entity/primitives/Teapot.h"

#include "shader/PhongShader.h"
#include "shader/NormalDebugShader.h"
#include "shader/SkyboxShader.h"

int winWidth = 500;
int winHeight = 500;
std::string winTitle = "Floating islands";
int fps = 1000 / 60;

int mouseX = 0;
int mouseY = 0;
int mouseDx = 0;
int mouseDy = 0;

bool drawDebugNormals = false;

std::shared_ptr<Camera> camera1;
std::shared_ptr<Camera> camera2;
std::shared_ptr<Camera> activeCamera;

std::shared_ptr<PhongShader> shader;
std::shared_ptr<NormalDebugShader> normalDebugShader;
std::shared_ptr<SkyboxShader> skyboxShader;

std::shared_ptr<Lighting> lighting;
std::shared_ptr<Cubemap> cubemap;
std::shared_ptr<Skybox> skybox;

std::shared_ptr<Quad> quad;
std::shared_ptr<Quad> quad2;
std::shared_ptr<Cube> cube;
std::shared_ptr<Teapot> teapot;
std::shared_ptr<Capacitor> capacitor;
std::shared_ptr<C4> c4;
std::shared_ptr<TestSurface> test;

TwBar* bar;

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthMask(GL_FALSE);
	skyboxShader->use();
		skybox->render(*skyboxShader, *activeCamera);
	glDepthMask(GL_TRUE);

	shader->use();
	lighting->setUniforms(*shader);

	quad->render(*shader, *activeCamera);
	quad2->render(*shader, *activeCamera);
	cube->render(*shader, *activeCamera);
	teapot->render(*shader, *activeCamera);
	capacitor->render(*shader, *activeCamera);
	c4->render(*shader, *activeCamera);
	test->render(*shader, *activeCamera);

	if (drawDebugNormals) {
		normalDebugShader->use();
		capacitor->render(*normalDebugShader, *activeCamera);
		quad2->render(*normalDebugShader, *activeCamera);
		cube->render(*normalDebugShader, *activeCamera);
		c4->render(*normalDebugShader, *activeCamera);
		test->render(*normalDebugShader, *activeCamera);
	}

	TwDraw();

	glutSwapBuffers();
}

void update(int delta)
{
	Game::time = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME);

	quad->update();
	quad2->update();
	cube->update();
	teapot->update();
	capacitor->update();
	c4->update();
	test->update();

	glutTimerFunc(fps, update, 0);
	glutPostRedisplay();
}

void initUI()
{
	TwInit(TW_OPENGL_CORE, NULL);
	bar = TwNewBar("Tweak bar");
    TwSetParam(bar, NULL, "iconified", TW_PARAM_CSTRING, 1, "true");
}

void init()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearStencil(0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	initUI();

	// Create cameras
	camera1 = std::make_shared<Camera>(winWidth, winHeight, glm::vec3(0, 0, 0));
	camera1->setZNear(0.2f);
	camera1->setZFar(100.0f);

	activeCamera = camera1;

	// Create shaders
	shader = std::make_shared<PhongShader>("data/shaders/phongVert.glsl", "data/shaders/phongFrag.glsl");

	std::string geoShader = "data/shaders/normalDebugGeo.glsl";
	normalDebugShader = std::make_shared<NormalDebugShader>("data/shaders/normalDebugVert.glsl", "data/shaders/normalDebugFrag.glsl", &geoShader);

	skyboxShader = std::make_shared<SkyboxShader>("data/shaders/skyboxVert.glsl", "data/shaders/skyboxFrag.glsl");

	// Create lights
	lighting = std::make_shared<Lighting>();

	PointLight* light1 = new PointLight();
	light1->transform.pos = glm::vec3(6, 4, 5);
	lighting->addLight(light1);

	PointLight* light2 = new PointLight();
	light2->transform.pos = glm::vec3(0, -2, 5);
	light2->color = glm::vec3(1.0, 0.0, 0.0);
	lighting->addLight(light2);

	PointLight* light3 = new PointLight();
	light3->transform.pos = glm::vec3(-3, -1.5, 0.5);
	lighting->addLight(light3);

	PointLight* light4 = new PointLight();
	light4->intensity = 2.0f;
	light4->radius = 15;
	light4->transform.pos = glm::vec3(2, 7, 3);
	lighting->addLight(light4);

	PointLight* light5 = new PointLight();
	light4->radius = 8;
	light5->transform.pos = glm::vec3(6, 7, 1);
	lighting->addLight(light5);

	PointLight* light6 = new PointLight();
	light6->radius = 20.0f;
	light6->transform.pos = glm::vec3(4, 10, 2);
	lighting->addLight(light6);

	SunLight* sun = new SunLight();
	sun->color = glm::vec3(0.93, 0.98, 1.0);
	sun->direction = glm::vec3(0.5, 0.5, -1);
	lighting->addLight(sun);

	SpotLight* spot = new SpotLight();
	spot->intensity = 0.4f;
	spot->transform.pos = glm::vec3(4, 3, 6);
	spot->direction = glm::vec3(3, -1.5, -6);
	lighting->addLight(spot);

	// Create objects
	quad = std::make_shared<Quad>();
	quad->create(shader);
	quad->transform.pos = glm::vec3(0, -10, -1);
	quad->transform.scale = glm::vec3(100);

	quad2 = std::make_shared<Quad>();
	quad2->create(shader);
	quad2->transform.pos = glm::vec3(6, 7, -0.5);
	quad2->transform.scale = glm::vec3(3);
	quad2->material->shininess = 100;
	quad2->texture = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-diffuse.jpg", "diffuse");
	quad2->specularMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-specular.jpg", "specular");
	quad2->aoMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-ao.jpg", "ao");
	quad2->normalMap = std::make_shared<Texture>("data/textures/stone_floor_4-2K/2K-stone_floor_4-normal.jpg", "normal");

	cube = std::make_shared<Cube>();
	cube->transform.pos = glm::vec3(0, -3, 0);
	cube->create(shader);

	teapot = std::make_shared<Teapot>();
	teapot->create(shader);
	teapot->transform.pos = glm::vec3(8, 0, 0);

	capacitor = std::make_shared<Capacitor>();
	capacitor->create(shader);
	capacitor->transform.pos = glm::vec3(0, 7, -1);
	capacitor->transform.scale = glm::vec3(3);

	c4 = std::make_shared<C4>();
	c4->create(shader);
	c4->transform.pos = glm::vec3(0, 4, 0);
	c4->transform.scale = glm::vec3(1);

	test = std::make_shared<TestSurface>();
	test->create(shader);
	test->transform.pos = glm::vec3(4, 10,-1);
	test->transform.scale = glm::vec3(0.5f);

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
	TwWindowSize(winWidth, winHeight);
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
	switch (keyPressed) {
		case 27: // escape
			#ifndef __APPLE__
				glutLeaveMainLoop();
			#else
				exit(0);
			#endif
			break;
	}
    TwEventKeyboardGLUT(keyPressed, mouseX, mouseY);
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
			drawDebugNormals = !drawDebugNormals;
			break;
	}
    TwEventSpecialGLUT(specKeyPressed, mouseX, mouseY);
	InputManager::keyMap[InputManager::glutSpecialKeyToImKey(specKeyPressed)] = true;
}

void specialKeyboardUpCb(int specKeyReleased, int mouseX, int mouseY) {
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
	TwEventMouseButtonGLUT(button, state, x, y);
    InputManager::mouseMap[InputManager::glutMouseButtonToImMouseButton(button)] = (state == GLUT_DOWN);
}

void mouseWheel(int wheel, int dir, int x, int y)
{
	mouseX = x;
	mouseY = y;
	activeCamera->mouseWheel(dir, 1);
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
	if (!TwEventMouseMotionGLUT(mouseX, mouseY)) {
		activeCamera->mouseDrag(mouseDx, mouseDy,
			InputManager::mouseMap[InputManager::IM_MOUSE_BUTTON_LEFT],
			InputManager::mouseMap[InputManager::IM_MOUSE_BUTTON_MIDDLE]
		);   
	}
}

/**
 * \brief Handle mouse movement over the window (with no button pressed).
 * \param x mouse (cursor) X position
 * \param y mouse (cursor) Y position
 */
void mouseMoved(int x, int y) {
	mouseX = x;
	mouseY = y;
	TwEventMouseMotionGLUT(mouseX, mouseY);
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

	TwTerminate();
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

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
