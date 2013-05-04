#include "BasicShaderProgram.h"

#include "Mesh.h"
#include "Transform.h"
#include "EngineData.h"
#include "Camera.h"
#include "UtilityFunctions.h"

BasicShaderProgram::BasicShaderProgram(void)
{
}

BasicShaderProgram::BasicShaderProgram(Mesh* newOwner, std::string fragmentShader, std::string vertexShader)
	: ShaderProgram(newOwner, fragmentShader, vertexShader)
{
	this->linkProgram();
}


BasicShaderProgram::~BasicShaderProgram(void)
{
}

void BasicShaderProgram::linkProgram(void) {

	//Bind the in-variables to vertex attribute indexes
	glBindAttribLocation( this->programID, 0, "in_Position");
	glBindAttribLocation( this->programID, 1, "in_Tex");
	glBindAttribLocation( this->programID, 2, "in_Normal");
	checkGLError( "Could not bind vertex Attribute Locations");

	//Link the uniform variables
	glLinkProgram( this->programID);
	checkGLError("Could not Link the Shader Program");

	this->modelMatrixUniform = glGetUniformLocation( this->programID, "ModelMatrix");
	this->viewMatrixUniform = glGetUniformLocation( this->programID, "ViewMatrix");
	this->projectionMatrixUniform = glGetUniformLocation( this->programID, "ProjectionMatrix");
	this->samplerUniform = glGetUniformLocation( this->programID, "s_tex" );
	checkGLError("Could not bind uniforms");
}

void BasicShaderProgram::linkVertexAttributes() {
	
	//Bind the vertex attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	checkGLError("Could not enable Vertex Attributes");
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(float)*3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(float)*3+sizeof(float)*2));
	checkGLError("Could not set the Vertex Attribute");
}

void BasicShaderProgram::updateUniforms(void) {
	glUseProgram(this->programID);

	glm::mat4 modelMatrix = *this->owner->getTransform()->getTransformMatrix();
	glm::mat4 viewMatrix = *EngineData::getActiveCamera()->transform.getTransformMatrix();
	glm::mat4 projectionMatrix = EngineData::getActiveCamera()->ProjectionMatrix;

	glUniformMatrix4fv(this->modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	checkGLError("Could not update uniforms1");
	glUniformMatrix4fv(this->viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	checkGLError("Could not update uniforms2");
	glUniformMatrix4fv(this->projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	checkGLError("Could not update uniforms3");
}