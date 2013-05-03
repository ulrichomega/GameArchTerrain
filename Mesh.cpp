#include "Mesh.h"

Mesh::Mesh(void) 
{
}

Mesh::Mesh(GameObject* owner)
{
	this->owner = owner;
	EngineData::addMesh(this);
	this->createMesh();
}


Mesh::~Mesh(void)
{
	EngineData::removeMesh(this);
}

void Mesh::draw() {

}

void Mesh::createMesh() {
	this->createShader();
}
void Mesh::createShader() {

}