#include "NormalShaderProgram.h"

#include "Mesh.h"
#include "Transform.h"
#include "EngineData.h"
#include "Camera.h"
#include "UtilityFunctions.h"
#include "Light.h"

NormalShaderProgram::NormalShaderProgram(void)
{
}

NormalShaderProgram::NormalShaderProgram(Mesh* newOwner)
	: ShaderProgram(newOwner, "normalmapPoint.fs", "normalmapPoint.vs")
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

	this->lightPosUniform = glGetUniformLocation(this->programID, "LightPosition");
	this->lightColorUniform = glGetUniformLocation(this->programID, "LightColor");
	this->lightBrightnessUniform = glGetUniformLocation(this->programID, "LightBrightness");

	this->ambientUniform = glGetUniformLocation(this->programID, "ambient");
	this->diffuseUniform = glGetUniformLocation(this->programID, "diffuse");
	this->specularUniform = glGetUniformLocation(this->programID, "specular");

	this->samplerUniform = glGetUniformLocation( this->programID, "s_tex" );
	this->normalMapUniform = glGetUniformLocation(this->programID, "s_normal");
	checkGLError("Could not bind uniforms");
}

void NormalShaderProgram::linkVertexAttributes() {
	this->enableVertexAttribArray();
	
	//Set the attribute offsets
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, uvPos));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, tangent));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, bitangent));
	checkGLError("Could not set the Vertex Attribute");
	
	this->disableVertexAttribArray();
}

void NormalShaderProgram::updateUniforms(void) {
	glm::mat4 modelMatrix = *this->owner->getTransform()->getTransformMatrix();
	glm::mat4 viewMatrix = *EngineData::getActiveCamera()->transform.getTransformMatrix();
	glm::mat4 projectionMatrix = EngineData::getActiveCamera()->ProjectionMatrix;
	glm::mat4 normalMatrix = this->calculateNormalMatrix();

	glUniformMatrix4fv(this->modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(this->viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(this->projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	//Get a vec3 from the light's transform matrix
	glm::vec3 lightPos = (glm::vec3)(*EngineData::getActiveLight()->transform.getTransformMatrix() * glm::vec4(0.0f,0.0f,0.0f,1.0f));
	glUniform3fv(this->lightPosUniform, 1, glm::value_ptr(lightPos));
	glUniform3fv(this->lightColorUniform, 1, glm::value_ptr(EngineData::getActiveLight()->color));
	glUniform1f(this->lightBrightnessUniform, EngineData::getActiveLight()->brightness);
	
	glm::vec3 ambient(0.05f,0.05f, 0.05f);
	glUniform3fv(this->ambientUniform, 1, glm::value_ptr(ambient));
	glm::vec3 diffuse(0.5f,0.5f, 0.5f);
	glUniform3fv(this->diffuseUniform, 1, glm::value_ptr(diffuse));
	glm::vec3 specular(0.7f,0.7f, 0.7f);
	glUniform3fv(this->specularUniform, 1, glm::value_ptr(specular));

	checkGLError("Could not update shininess uniforms");
}

glm::mat4 NormalShaderProgram::calculateNormalMatrix(void){
	glm::mat4 modelMatrix = *this->owner->getTransform()->getTransformMatrix();
	glm::mat4 normalMatrix;

	normalMatrix[0][0] = modelMatrix[0][0];
	normalMatrix[0][1] = modelMatrix[0][1];
	normalMatrix[0][2] = modelMatrix[0][2];
	normalMatrix[1][0] = modelMatrix[1][0];
	normalMatrix[1][1] = modelMatrix[1][1];
	normalMatrix[1][2] = modelMatrix[1][2];
	normalMatrix[2][0] = modelMatrix[2][0];
	normalMatrix[2][1] = modelMatrix[2][1];
	normalMatrix[2][2] = modelMatrix[2][2];

	normalMatrix = glm::transpose( glm::inverse(normalMatrix));
	return normalMatrix;
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

void NormalShaderProgram::setTextureUnit(int typeOfTexture, int texUnit) {
	switch (typeOfTexture) {
	case 0:
		glUniform1i(this->samplerUniform, texUnit);
		break;
	case 1:
		glUniform1i(this->normalMapUniform, texUnit);
		break;
	}
}