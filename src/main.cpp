#include "pgr.h"
#include <iostream>

#include "entity/Camera.h"
#include "Game.h"
#include "Lighting.h"
#include "entity/lights/PointLight.h"
#include "entity/lights/SunLight.h"
#include "entity/primitives/Cube.h"
#include "parser/ObjParser.h"
#include "shader/PhongShader.h"
#include "entity/primitives/Quad.h"

int winWidth = 500;
int winHeight = 500;
std::string winTitle = "Floating islands";
int fps = 1000 / 60;

int mouseX = 0;
int mouseY = 0;
int mouseDx = 0;
int mouseDy = 0;

bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;

std::shared_ptr<Camera> camera;
std::shared_ptr<PhongShader> shader;

std::shared_ptr<Lighting> lighting;

std::shared_ptr<Quad> quad;
std::shared_ptr<Cube> cube;
std::shared_ptr<Cube> cube2;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    lighting->setUniforms(*shader);

    quad->render(camera);
	cube->render(camera);
    cube2->render(camera);

    glutSwapBuffers();
}

void update(int delta)
{
    Game::time = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME);

    quad->update();
    cube->update();
    cube2->update();

    // and plan a new event
    glutTimerFunc(fps, update, 0);

    // create display event
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearStencil(0);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_MULTISAMPLE);

    camera = std::make_shared<Camera>(winWidth, winHeight, glm::vec3(0, 0, 0));
    camera->setZNear(0.2f);
	camera->setZFar(70.0f);

    shader = std::make_shared<PhongShader>("data/shaders/phongVert.glsl", "data/shaders/phongFrag.glsl");

    lighting = std::make_shared<Lighting>();

    PointLight* light1 = new PointLight();
    light1->position = glm::vec3(3, 2, 1);
    lighting->addLight(light1);

    PointLight* light2 = new PointLight();
    light2->position = glm::vec3(3, -2, 1);
    light2->color = glm::vec3(1.0, 0.0, 0.0);
    lighting->addLight(light2);

    SunLight* sun = new SunLight();
    lighting->addLight(sun);

    quad = std::make_shared<Quad>();
    quad->create(shader);
    quad->position = glm::vec3(0, 0, -1);
    quad->scale = glm::vec3(100);

    cube = std::make_shared<Cube>();
    cube->create(shader);

    cube2 = std::make_shared<Cube>();
    cube2->create(shader);
    cube2->position = glm::vec3(8, 0, 0);

    ObjParser parser("cube.obj");
    std::vector<float> vbo;
    std::vector<unsigned int> ebo;
    parser.getDrawElementsGeo(vbo, ebo);
    std::cout << "Triangle count: " << parser.getTriangleCount() << std::endl;

    //// initialize shaders
    //initializeShaderPrograms();
    //// create geometry for all models used
    //initializeModels();
}

void reshape(int newWidth, int newHeight) {
    winWidth = newWidth;
    winHeight = newHeight;
    glViewport(0, 0, winWidth, winHeight);
    camera->size(newWidth, newHeight);
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
}

void specialKeyboardUpCb(int specKeyReleased, int mouseX, int mouseY) {
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
	if (button == GLUT_LEFT_BUTTON) {
        mouseLeftDown = (state == GLUT_DOWN);
    } else
    if (button == GLUT_RIGHT_BUTTON) {
        mouseRightDown = (state == GLUT_DOWN);
    } else 
    if (button == GLUT_MIDDLE_BUTTON) {
        mouseMiddleDown = (state == GLUT_DOWN);
    }
}

void mouseWheel(int wheel, int dir, int x, int y)
{
    mouseX = x;
    mouseY = y;
    camera->mouseWheel(dir, 1);
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
	camera->mouseDrag(mouseDx, mouseDy, mouseLeftDown, mouseMiddleDown);
}

/**
 * \brief Handle mouse movement over the window (with no button pressed).
 * \param x mouse (cursor) X position
 * \param y mouse (cursor) Y position
 */
void mouseMoved(int x, int y) {
    mouseX = x;
    mouseY = y;
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

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // for each window
    {
        //   initial window size + title
        glutInitWindowSize(winWidth, winHeight);
        glutCreateWindow(winTitle.c_str());

        // Callbacks - use only those you need
        glutDisplayFunc(render);
        glutReshapeFunc(reshape);
        // glutKeyboardFunc(keyboardCb);
        // glutKeyboardUpFunc(keyboardUpCb);
        // glutSpecialFunc(specialKeyboardCb);     // key pressed
        // glutSpecialUpFunc(specialKeyboardUpCb); // key released
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
