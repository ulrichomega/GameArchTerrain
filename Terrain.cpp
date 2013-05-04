#include "Terrain.h"

#include "Mesh.h"

Terrain::Terrain(void)
{
	this->mesh = new Mesh(this);
	//this->transform.transformMatrix = glm::scale(this->transform.transformMatrix, glm::vec3(0.1f));
	this->transform.moveForward(-2.0f);
	//for (int x = 0; x < 4; x++) {
	//	for (int y = 0; y < 4; y++) {
	//		std::cout << this->transform.getTransformMatrix()[x][y];
	//	}
	//	std::cout << std::endl;
	//}
}


Terrain::~Terrain(void)
{
	delete this->mesh;
}

void Terrain::update(double deltaT) {

}