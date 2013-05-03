#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <string>
#include <iostream>

//In-Project
#include "shader.h"
class Mesh;

class ShaderProgram
{
public:
	friend class Mesh;
	ShaderProgram(void);
	ShaderProgram(Mesh* newOwner, std::string fragmentShader, std::string vertexShader);
	~ShaderProgram(void);

	void setShader(std::string filename, GLenum shaderType);

protected:
	void loadProgram(void);
	virtual void linkProgram(void) = 0;
	virtual void updateUniforms(void) = 0;

	Mesh* owner;

	GLuint programID;

	shader fragmentShader;
	shader vertexShader;
};

