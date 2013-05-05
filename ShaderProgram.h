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

	/*Program must:
		Bind the attribute locations (the "in_-" variables) to vertex attribute locations
		Call glLinkProgram with the program's programID
		Assign and keep track of the uniform locations
	*/
	virtual void linkProgram(void) = 0;
	/*Program must:
		Assume that the vertexAttributeArray is actively bound
		Enable the Vertex Attributes associated with the AttribLocations from LinkProgram
		Assign Vertex Attribute Pointers
	*/
	virtual void linkVertexAttributes(void) = 0;
		/*Program must:
			Update all the uniforms it assigned
		*/
	virtual void updateUniforms(void) = 0;

		/*Program must:
			Enable all vertexAttribArray bindings
		*/
	virtual void enableVertexAttribArray(void) = 0;

		/*Program must:
			Enable all vertexAttribArray bindings
		*/
	virtual void disableVertexAttribArray(void) = 0;

	Mesh* owner;

	GLuint programID;

	shader fragmentShader;
	shader vertexShader;
};

