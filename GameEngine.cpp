#include "GameEngine.h"

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

}

void GameEngine::initializeOpenGL() {
	//Initialize Window
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (!glfwOpenWindow(EngineData::getWindowWidth(), EngineData::getWindowHeight(), 0,0,0,0, 16,0, GLFW_WINDOW) ) {
		exit(EXIT_FAILURE);
	}

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();

	if (GLEW_OK != glewInitResult) {	//Did GLEW initialize correctly?
		exit(EXIT_FAILURE);//Should probably print something out or something
	}

	//Set openGL standard values
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//glfwSetCharCallback ( *handleKeyboard );
	/*NOTE:
	Cannot set class functions as glfw Callback functions. Have to move this 
	to the main somehow. That's a job for tomorrow, though. 
	*/
}

void GLFWCALL GameEngine::handleKeyboard(int character, int action) {
	
}