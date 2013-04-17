#pragma once

//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class EngineData
{
public:
	friend class GameEngine;
	EngineData(void);
	~EngineData(void);
private:
	//Window information, supports one (1) window for now
	static int windowHeight;
	static int windowWidth;
	static int windowHandle;

	//Time data
	static double currentTime;
	static double pastTime;
	static double deltaTime;
	static double startTime;

	//Matrices
	static glm::mat4 ProjectionMatrix = glm::perspective(60.0f, 16.0f/9.0f, 0.1f, 100.0f);

};

