#include "NormalShaderProgram.h"

#include "Mesh.h"
#include "Transform.h"
#include "EngineData.h"
#include "Camera.h"
#include "UtilityFunctions.h"

NormalShaderProgram::NormalShaderProgram(void)
{
}

NormalShaderProgram::NormalShaderProgram(Mesh* newOwner)
	: ShaderProgram(newOwner, "normalMap.fs", "normalMap.vs")
{
	this->linkProgram();
}


NormalShaderProgram::~NormalShaderProgram(void)
{
}

void NormalShaderProgram::linkProgram(void) {

	//Bind the in-variables to vertex attribute indexes
	glBindAttribLocation( this->programID, 0, "in_Position");
	glBindAttribLocation( this->programID, 1, "in_Tex");
	glBindAttribLocation( this->programID, 2, "in_Normal");
	glBindAttribLocation( this->programID, 3, "in_Tangent");
	glBindAttribLocation( this->programID, 4, "in_Bitangent");
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

void NormalShaderProgram::linkVertexAttributes() {
	
	//Active the vertex attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	checkGLError("Could not enable Vertex Attributes");
	
	//Set the attribute offsets
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, uvPos));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, tangent));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, bitangent));
	checkGLError("Could not set the Vertex Attribute");
}

void NormalShaderProgram::updateUniforms(void) {
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

void NormalShaderProgram::enableVertexAttribArray(void) {
	//Active the vertex attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	checkGLError("Could not enable Vertex Attributes");
}

void NormalShaderProgram::disableVertexAttribArray(void) {
	//Active the vertex attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	checkGLError("Could not enable Vertex Attributes");
}