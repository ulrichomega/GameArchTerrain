#include "Terrain.h"

#include "Mesh.h"

Terrain::Terrain(void)
{
	this->mesh = new Mesh(this);
}


Terrain::~Terrain(void)
{
	delete this->mesh;
}

void Terrain::update(double deltaT) {

}

void Terrain::draw() {
	this->mesh->draw();
}