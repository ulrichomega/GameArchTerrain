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

class NormalShaderProgram : 
	public ShaderProgram
{
public:
	friend class Mesh;
	NormalShaderProgram(void);
	NormalShaderProgram(Mesh* newOwner);
	~NormalShaderProgram(void);
	
	void setTextureUnit(int typeOfTexture, int texUnit);

protected:
	void updateUniforms(void);
	GLuint samplerUniform;
	GLuint normalMapUniform;

private:
	//Uniform matrix locations
	GLuint modelMatrixUniform;
	GLuint viewMatrixUniform;
	GLuint projectionMatrixUniform;

	//Vertex Shader uniforms
	GLuint lightPosUniform;

	//Fragment Shader uniforms
	GLuint lightColorUniform;
	GLuint lightBrightnessUniform;
	GLuint ambientUniform;
	GLuint diffuseUniform;
	GLuint specularUniform;

	void linkProgram(void);
	void linkVertexAttributes(void);
	glm::mat4 calculateNormalMatrix(void);
	void enableVertexAttribArray(void);
	void disableVertexAttribArray(void);
};

