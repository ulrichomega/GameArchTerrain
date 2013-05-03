#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library

//In-Project
#include "shader.h"

class ShaderProgram
{
public:
	ShaderProgram(void);
	~ShaderProgram(void);
private:
	shader vertexShader;
	shader pixelShader;
};

