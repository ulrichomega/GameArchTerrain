#include "ShaderProgram.h"
#include "Mesh.h"

ShaderProgram::ShaderProgram(void)
{
}

ShaderProgram::ShaderProgram(Mesh* newOwner, std::string fragmentShader, std::string vertexShader){
	this->owner = owner;
	this->fragmentShader = shader(fragmentShader, GL_FRAGMENT_SHADER);
	this->vertexShader = shader(vertexShader, GL_VERTEX_SHADER);

	this->loadProgram();
}

ShaderProgram::~ShaderProgram(void)
{
}

void ShaderProgram::loadProgram(void){
	this->programID = glCreateProgram();

	glAttachShader(this->programID, this->fragmentShader.shaderID);
	glAttachShader(this->programID, this->vertexShader.shaderID);

	this->linkProgram();
}

void ShaderProgram::setShader(std::string filename, GLenum shaderType) {
	if (shaderType == GL_FRAGMENT_SHADER) {
		this->fragmentShader = shader(filename, GL_FRAGMENT_SHADER);
	}
	else if (shaderType == GL_VERTEX_SHADER) {
		this->vertexShader = shader(filename, GL_VERTEX_SHADER);
	}
	else {
		std::cout << "Could not load shader, invalid shaderType." << std::endl;
		throw "Could not load shader, invalid shadertype.";
	}
}