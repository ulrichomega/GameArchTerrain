#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct vertex {
	GLfloat position[3];
    GLfloat uvPos[2];
    GLfloat normal[3];
	bool operator==(const vertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(vertex))==0;
	};
};