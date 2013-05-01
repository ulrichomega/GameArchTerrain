#include "GameEngine.h"

//function prototypes
void initializeOpenGL();

GameEngine::GameEngine(void)
{

}


GameEngine::~GameEngine(void)
{
}


void GameEngine::run() {
	EngineData::initializeData();

	bool running = true;
	while (running) {
		updateTime();
		update();
		draw();
	}
}

void GameEngine::setup() {
	Camera activeCamera();

	initializeOpenGL();
}

void GameEngine::updateTime() {
	EngineData::updateTime();
}

void GameEngine::update() {

}

void GameEngine::draw() {

}

void initializeOpenGL() {
	//Initialize Window
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (!glfwOpenWindow(EngineData::windowWidth, EngineData::windowHeight, 0,0,0,0, 16,0, GLFW_WINDOW) ) {
		exit(EXIT_FAILURE);
	}
}
