#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
class shader
{
public:
	shader(void);
	shader(const char* filename, GLenum shader_type);
	~shader(void);

	GLuint shaderID;
	std::vector<GLuint> uniforms;

	GLuint LoadShader(const char* filename, GLenum shader_type);
};

