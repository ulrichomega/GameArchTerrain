#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.h"
#include "EngineData.h"

class Mesh
{
public:
	Mesh(GameObject* owner);

	~Mesh(void);
	
private:
	GameObject* owner;
};

