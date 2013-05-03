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
#include <cstddef>	//offsetof
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//In-Project
class GameObject;
class BasicShaderProgram;
class Transform;
#include "vertex.h"

//Mesh is a component of a GameObject
/*
	The Mesh interface contains all methods needed to draw a series of vertices
	to the screen. 
	Meshes register themselves with EngineData so that they may be rendered.
	A Mesh requires a GameObject to exist.
*/
class Mesh
{
public:
	Mesh(void);
	Mesh(GameObject* owner);

	~Mesh(void);

	void draw();
	friend class ShaderProgram;
	friend class BasicShaderProgram;	//Isn't friendship inherited?

protected:
	Transform* getTransform();
	
private:
	GameObject* owner;
	BasicShaderProgram* shader;

	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint vertexIndexID;
	GLuint textureID;

	std::vector<vertex> vertices;
	std::vector<int> vertexIndices;

	void createMesh();
	void loadOBJ(std::string fileName);
	void createShader();
	void createBuffers();
	void createTexture(std::string filename);
	
};

