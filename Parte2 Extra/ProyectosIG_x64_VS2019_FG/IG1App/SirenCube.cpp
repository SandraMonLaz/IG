#include "SirenCube.h"
#include "EntityWithMaterial.h"

SirenCube::SirenCube(Texture* arriba, Texture* lateral, int r, SpotLight* sp): siren(sp), radioOrbita(r), angle(0)
{
	Esfera* es = new Esfera(20, 50, 20, dvec4(1.0f, 0.0f, 0.0f, 1.0f));
	es->setModelMat(translate(dmat4(1), dvec3(0, 100, 0)));

	GridCube* g = new GridCube(arriba, lateral);

	addEntity(g);
	addEntity(es);

	setModelMat(translate(dmat4(1), dvec3(0, radioOrbita, 0)));
	setModelMat(scale(modelMat(), dvec3(0.3, 0.3, 0.3)));
	fvec3 dir = { 0.0, -1.0,0.5 };
	siren->setSpot(dir,20,5);

	//glm::fvec4 posDir = { 1, 1, 1, 0 };
	//fvec3 posDir = {0,radioOrbita +30, 0};
	//fvec3 posDir = {0,0,0};
	//siren->setPosDir(posDir);
}


void SirenCube::move()
{
	//Rotamos el objeto desde el pivote del (0,0,0)
	double compZ = radioOrbita*sin(radians(angle));
	double compY = radioOrbita* cos(radians(angle));
	setModelMat(translate(dmat4(1),dvec3(0,compY,compZ)));
	setModelMat(rotate(mModelMat, glm::radians(angle), dvec3(1, 0, 0)));
	setModelMat(scale(modelMat(), dvec3(0.3, 0.3, 0.3)));

	angle++;
	//matrizLuz = rotate(dmat4(1), glm::radians(angle), dvec3(1, 0, 0));
	//matrizLuz = rotate(matrizLuz, glm::radians(angle*10), dvec3(0, 1, 0));

}

void SirenCube::render(glm::dmat4 const& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
	glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	aMat = rotate(aMat,radians(angle*4),dvec3(0,1,0));
	siren->upload(aMat);
}


