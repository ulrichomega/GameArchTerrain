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
#include "ShaderProgram.h"

//BasicShader implements ShaderProgram on the shaders "basic.fs" and "basic.vs"
class BasicShaderProgram : public ShaderProgram
{
public:
	friend class Mesh;
	friend class CubeMap;
	BasicShaderProgram(void);
	BasicShaderProgram(Mesh* newOwner);
	~BasicShaderProgram(void);
	void setTextureUnit(int typeOfTexture, int texUnit);

protected:
	void updateUniforms(void);

private:
	//Uniform locations
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;
	GLuint samplerUniform;

	void linkProgram(void);
	void linkVertexAttributes(void);
	void enableVertexAttribArray(void);
	void disableVertexAttribArray(void);
};

