#include "Mesh.h"

Mesh::Mesh(void) 
{
}

Mesh::Mesh(GameObject* owner)
{
	this->owner = owner;
	EngineData::addMesh(this);
}


Mesh::~Mesh(void)
{
	EngineData::removeMesh(this);
}

void Mesh::draw() {

}