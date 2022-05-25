#include "pgr.h"
#include <iostream>

#include "Game.h"
#include "InputManager.h"
#include "Lighting.h"

#include "shader/GrassShader.h"
#include "shader/PhongShader.h"
#include "shader/NormalDebugShader.h"
#include "shader/SkyboxShader.h"

#include "scene/Scene.h"
#include "scene/IslandScene.h"
#include "entity/Camera.h"
#include "entity/general/Empty.h"

#include "Skybox.h"
#include "texture/Cubemap.h"

#include "imgui_impl_glut.h"
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
	camera1->radius = 34;
	camera1->rotationX = -34;
	camera1->rotationY = -30;
	scene->add(camera1.get());

	camera2 = std::make_shared<Camera>(winWidth, winHeight, glm::vec3(0, 5, 0));
	camera2->setName("Camera 2");
	camera2->create(shader.get());

	airshipCamera = std::make_shared<Camera>(winWidth, winHeight, glm::vec3(0, 0, 0));
	airshipCamera->setName("Camera 3 (Airship)");
	airshipCamera->rotationX = -90;
	airshipCamera->create(shader.get());

	activeCamera = camera1;

	// Create lighting
	lighting = std::make_shared<Lighting>();

	// Creates most lights and game objects
	createIslandScene(scene.get(), lighting.get(), Game::textures.get(), shader.get(), grassShader.get(), airshipCamera.get());

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
			activeCamera = camera1;
			activeCamera->size(winWidth, winHeight);
			break;
		case GLUT_KEY_F2:
			activeCamera = camera2;
			activeCamera->size(winWidth, winHeight);
			break;
		case GLUT_KEY_F3:
			activeCamera = airshipCamera;
			activeCamera->size(winWidth, winHeight);
			break;
		case GLUT_KEY_F4:
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
