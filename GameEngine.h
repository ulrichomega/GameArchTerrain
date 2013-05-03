#pragma once

//OpenGL + GLFW
#include "glew.h" //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <vector>
#include <iostream>

//In-Project
//class GameEngine;
#include "EngineData.h"
#include "Camera.h"

class GameEngine
{
public:
	GameEngine(void);
	~GameEngine(void);

	void run();
	void setup();
	
	void handleKeyboard(int, int);
	void handleMouse(int, int);
	void handleMousePos(int, int);
	void handleMouseWheel(int);

private:
	void updateTime();
	void update();
	void draw();
	void initializeOpenGL();
	void exitEngine();

	bool running;
};

