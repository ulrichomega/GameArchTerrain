#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <vector>
#include <string>
#include <iostream>

//In-Project
//class shader;

class shader
{
public:
	friend class ShaderProgram;
	shader(void);
	shader(std::string filename, GLenum shaderType);
	~shader(void);

	//std::vector<GLuint> uniforms;
protected:
	GLuint shaderID;
private:
	void LoadShader(const char* filename, GLenum shaderType);
	void checkShader();
};

