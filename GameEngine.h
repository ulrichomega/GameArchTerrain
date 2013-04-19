#pragma once

//OpenGL + GLFW
#include "glew.h" //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Other
#include "EngineData.h"

class GameEngine
{
public:
	GameEngine(void);
	~GameEngine(void);

	void run();

private:
	void updateTime();
	void update();
	void draw();
};

