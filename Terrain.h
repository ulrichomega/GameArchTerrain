#pragma once

//OpenGL + GLFW
#include "glew.h" //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <iostream>

//In-Project
//class Terrain;
#include "GameObject.h"
class heightMap;

class Terrain : public GameObject
{
public:
	Terrain(void);
	~Terrain(void);

	void update(double deltaT);
	void draw();

private: 
	heightMap* mesh;
};

