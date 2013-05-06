#include "Terrain.h"

#include "HeightMap.h"

Terrain::Terrain(void)
{
	this->mesh = new heightMap(this, "THIS ISN'T BEING USED RIGHT NOW");
	this->transform.moveForward(-this->mesh->ySize/4.0f);
	this->transform.moveSide(-this->mesh->xSize/4.0f);
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