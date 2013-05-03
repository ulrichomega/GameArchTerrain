#include "BasicShaderProgram.h"


BasicShaderProgram::BasicShaderProgram(void)
{
}

BasicShaderProgram::BasicShaderProgram(std::string fragmentShader, std::string vertexShader)
	: ShaderProgram(fragmentShader, vertexShader)
{
}


BasicShaderProgram::~BasicShaderProgram(void)
{
}

void BasicShaderProgram::linkProgram(void) {

	//Bind the in-variables to vertex attribute indexes
	glBindAttribLocation(this->programID, 0, "in_Position");
	glBindAttribLocation(this->programID, 1, "in_Tex");
	glBindAttribLocation(this->programID, 2, "in_Normal");

	//Link the uniform variables
	glLinkProgram(this->programID);

	this->modelMatrixUniform = glGetUniformLocation (this->programID, "ModelMatrix");
	this->viewMatrixUniform = glGetUniformLocation (this->programID, "ViewMatrix");
	this->projectionMatrixUniform = glGetUniformLocation (this->programID, "ProjectionMatrix");
}