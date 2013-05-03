#include "Mesh.h"


Mesh::Mesh(GameObject* owner)
{
	this->owner = owner;
	EngineData::addMesh(this);
}


Mesh::~Mesh(void)
{
}

void Mesh::draw() {

}