#include "Terrain.h"

#include "HeightMap.h"

Terrain::Terrain(void)
{
	this->mesh = new heightMap(this, "THIS ISN'T BEING USED RIGHT NOW");
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