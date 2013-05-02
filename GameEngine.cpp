#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
{
}


GameEngine::~GameEngine(void)
{
	delete this->activeCamera;
}


void GameEngine::run() {
	if (this->running) {return;}
	EngineData::initializeData();

	this->running = true;

	while (this->running) {
		updateTime();
		update();
		draw();
	}
}

void GameEngine::setup() {
	Camera* newCamera = new Camera();

	this->activeCamera = newCamera;

	initializeOpenGL();
}

void GameEngine::updateTime() {
	EngineData::updateTime();
}

void GameEngine::update() {

}

void GameEngine::draw() {
	glfwSwapBuffers();
}

void GameEngine::initializeOpenGL() {
	//Initialize Window
	if (!glfwInit()) {
		std::cout << "Could not initialize glfw" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (!glfwOpenWindow(EngineData::getWindowWidth(), EngineData::getWindowHeight(), 0,0,0,0, 16,0, GLFW_WINDOW) ) {
		std::cout << "Could not open window" << ": " << gluErrorString(glGetError()) << std::endl;
        glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowTitle("Terrain Project");

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();

	if (GLEW_OK != glewInitResult) {	//Did GLEW initialize correctly?
		std::cout << "Could not initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);//Should probably print something out or something
	}

	//Set openGL standard values
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void GameEngine::handleKeyboard(int key, int action) {
	if (key == GLFW_KEY_ESC) {
		this->exitEngine();
	}
}
void GameEngine::handleMouse(int button, int action) {

}
void GameEngine::handleMousePos(int x, int y) {

}
void GameEngine::handleMouseWheel(int position) {

}

void GameEngine::exitEngine() {
	glfwTerminate();
	this->running = false;
}