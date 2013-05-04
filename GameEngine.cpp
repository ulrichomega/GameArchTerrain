#include "GameEngine.h"

#include "EngineData.h"
#include "Mesh.h"
#include "Camera.h"
#include "UtilityFunctions.h"

GameEngine::GameEngine(void)
{
}


GameEngine::~GameEngine(void)
{

}


void GameEngine::run() {
	if (this->running) {return;}

	this->running = true;

	while (this->running) {
		this->updateTime();
		this->update();
		this->draw();
		if (!this->running) {
			std::cout << "I am going to quit, now" << std::endl;
			glfwTerminate();
		}
	}
}

void GameEngine::setup() {
	this->initializeOpenGL();
	EngineData::initializeData();
}

void GameEngine::updateTime() {
	EngineData::updateTime();
}

void GameEngine::update() {
	EngineData::getActiveCamera()->update(EngineData::getDeltaTime());
}

void GameEngine::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < EngineData::getMeshesToDraw()->size(); i++) {
		EngineData::getMeshesToDraw()->at(i)->draw();
	}

	glfwSwapBuffers();
}

void GameEngine::initializeOpenGL() {
	//Initialize Window
	if (GL_FALSE == glfwInit()) {
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
	
	//glewInit() always throw invalid_enum errors
	checkGLError("glewInit() threw an error. Ignore this");

	if (GLEW_OK != glewInitResult) {	//Did GLEW initialize correctly?
		std::cout << "Could not initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);//Should probably print something out or something
	}
	checkGLError("Could not initialize GLEW");
	
	//Set openGL standard values
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	checkGLError("Could not initialize openGL standard values");
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
	this->running = false;
}