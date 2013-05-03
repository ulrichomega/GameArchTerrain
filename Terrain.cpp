#include "Terrain.h"

#include "Mesh.h"

Terrain::Terrain(void)
{
	this->mesh = new Mesh(this);
}


Terrain::~Terrain(void)
{
}

void Terrain::update(double deltaT) {

}