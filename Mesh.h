#pragma once
//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//In-Project
class Mesh;
#include "GameObject.h"
#include "EngineData.h"
#include "ShaderProgram.h"


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
	
private:
	GameObject* owner;
	ShaderProgram shader;

	void createMesh();
	void createShader();
};

