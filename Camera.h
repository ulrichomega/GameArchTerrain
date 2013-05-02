#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.h"

//TODO: Implement rotation around point
class Camera : public GameObject
{
public:
	Camera(void);
	~Camera(void);
	
	glm::mat4 ProjectionMatrix;
};

