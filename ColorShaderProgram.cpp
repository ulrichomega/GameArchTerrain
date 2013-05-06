#include "ColorShaderProgram.h"

#include "Mesh.h"
#include "Transform.h"
#include "EngineData.h"
#include "Camera.h"
#include "UtilityFunctions.h"

ColorShaderProgram::ColorShaderProgram(void)
{
}

ColorShaderProgram::ColorShaderProgram(Mesh* newOwner) 
	: ShaderProgram(newOwner, "color.fs", "color.vs"){
	this->linkProgram();
}

ColorShaderProgram::~ColorShaderProgram(void)
{
}


void ColorShaderProgram::setTextureUnit(int typeOfTexture, int texUnit){

}

void ColorShaderProgram::updateUniforms(void){
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

void ColorShaderProgram::linkProgram(void){
	
	//Bind the in-variables to vertex attribute indexes
	glBindAttribLocation( this->programID, 0, "in_Position");
	glBindAttribLocation( this->programID, 1, "in_Color");
	glBindAttribLocation( this->programID, 2, "in_Normal");
	checkGLError( "Could not bind vertex Attribute Locations");

	//Link the uniform variables
	glLinkProgram( this->programID);
	checkGLError("Could not Link the Shader Program");

	this->modelMatrixUniform = glGetUniformLocation( this->programID, "ModelMatrix");
	this->viewMatrixUniform = glGetUniformLocation( this->programID, "ViewMatrix");
	this->projectionMatrixUniform = glGetUniformLocation( this->programID, "ProjectionMatrix");
	checkGLError("Could not bind uniforms");
}
void ColorShaderProgram::linkVertexAttributes(void){
	this->enableVertexAttribArray();
	
	//Set the attribute offsets
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, color));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
	checkGLError("Could not set the Vertex Attribute");

	this->disableVertexAttribArray();
}
void ColorShaderProgram::enableVertexAttribArray(void){
	//Active the vertex attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	checkGLError("Could not enable Vertex Attributes");
}
void ColorShaderProgram::disableVertexAttribArray(void){
	//Active the vertex attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	checkGLError("Could not enable Vertex Attributes");
}