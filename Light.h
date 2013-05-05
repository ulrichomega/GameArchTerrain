#pragma once

//OpenGL + GLFW
#include "glew.h" //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//In-Project
#include "gameobject.h"

class Light :
	public GameObject
{
public:
	Light(void);
	~Light(void);

	void update(double deltaT);
	glm::vec3 color;
	float brightness;
};

