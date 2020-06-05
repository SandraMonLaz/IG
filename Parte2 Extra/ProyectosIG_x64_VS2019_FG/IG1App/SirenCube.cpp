#include "SirenCube.h"
#include "EntityWithMaterial.h"

SirenCube::SirenCube(Texture* arriba, Texture* lateral, int r, SpotLight* sp): siren(sp)
{
	radioOrbita = r ;
	angle = 0;
	Esfera* es = new Esfera(20, 50, 20, dvec4(1.0f, 0.0f, 0.0f, 1.0f));
	es->setModelMat(translate(dmat4(1), dvec3(0, 100, 0)));
	GridCube* g = new GridCube(arriba, lateral);
	sirenCar = new CompoundEntity();
	sirenCar->addEntity(g);
	sirenCar->addEntity(es);
	sirenCar->setModelMat(translate(dmat4(1), dvec3(0, radioOrbita, 0)));
	sirenCar->setModelMat(scale(sirenCar->modelMat(), dvec3(0.3, 0.3, 0.3)));
	addEntity(sirenCar);
}


void SirenCube::move()
{
	//Rotamos el objeto desde el pivote del (0,0,0)
	this->setModelMat(rotate(dmat4(1), glm::radians(angle), dvec3(1, 0, 0)));
	angle++;
	matrizLuz = rotate(dmat4(1), glm::radians(angle), dvec3(1, 0, 0));
	matrizLuz = rotate(matrizLuz, glm::radians(angle*10), dvec3(0, 1, 0));

}

void SirenCube::render(glm::dmat4 const& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
	glm::dmat4 aMat = modelViewMat * matrizLuz;  // glm matrix multiplication
	siren->upload(aMat);
}


