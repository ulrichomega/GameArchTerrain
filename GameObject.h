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

//In-Project
//class GameObject
#include "Transform.h"

class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	virtual void update(double deltaT) = 0;
	
	Transform transform;

protected:
};

