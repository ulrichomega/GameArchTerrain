#include "ShaderProgram.h"
#include "Mesh.h"
#include "UtilityFunctions.h"

ShaderProgram::ShaderProgram(void)
{
}

ShaderProgram::ShaderProgram(Mesh* newOwner, std::string fragmentShader, std::string vertexShader){
	this->owner = newOwner;
	this->fragmentShader = shader(fragmentShader, GL_FRAGMENT_SHADER);
	this->vertexShader = shader(vertexShader, GL_VERTEX_SHADER);
	this->loadProgram();

	//All inheriting ShaderPrograms must also define and call LinkProgram() in constructor
}

ShaderProgram::~ShaderProgram(void)
{
}

void ShaderProgram::loadProgram(void){
	this->programID = glCreateProgram();
	checkGLError("Could not create program");

	glAttachShader(this->programID, this->fragmentShader.shaderID);
	glAttachShader(this->programID, this->vertexShader.shaderID);
	checkGLError("Could not attach shaders to program");
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