#include "Avion.h"
#include "EntityWithIndexMesh.h"
#include "QuadricEntity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
using namespace glm;
Avion::Avion(int r, SpotLight* faro) : CompoundEntity(), angle(0), heliceAngle(0),luzFoco(faro), radioOrbita(r)
{
	//Helices---------------------------------------
	Cylinder* heliceIzq = new Cylinder(200, 100, 400);
	heliceIzq->setColor(glm::fvec3(0.0f, 0.0f, 1.0f));
	heliceIzq->setModelMat(rotate(dmat4(1), glm::radians(90.0), dvec3(0, 1, 0)));

	Cylinder* heliceDcha = new Cylinder(200, 100, 400);
	heliceDcha->setColor(glm::fvec3(0.0f, 0.0f, 1.0f));
	heliceDcha->setModelMat(rotate(dmat4(1), glm::radians(-90.0), dvec3(0, 1, 0)));

	CompoundEntity* helices = new CompoundEntity();
	helices->addEntity(heliceDcha);
	helices->addEntity(heliceIzq);
	helices->setModelMat(translate(glm::dmat4(1), dvec3(0, 0, 230)));
	helices->setModelMat(scale(helices->modelMat(), glm::dvec3(0.3, 0.2, 0.2)));

	helicesAvion = helices;
	//Chasis---------------------------------------
	Sphere* bola = new Sphere(200);
	bola->setColor(glm::fvec3(1.0f, 0.0f, 0.0f));
	CompoundEntity* chasis = new CompoundEntity();
	chasis->addEntity(bola);
	chasis->addEntity(helices);
	//Alas---------------------------------------
	Cubo* alas = new Cubo(glm::dvec4(0.0f, 1.0f, 0.0f, 1.0f));
	alas->setModelMat(scale(glm::dmat4(1), glm::dvec3(8, 0.4, 2)));
	alas->setCopper(true);
	
	///Esto se hizo en la entrega de "Practica 2" se ha corregido 
	/*CompoundEntity* avion = new CompoundEntity();
	avion->addEntity(alas);
	avion->addEntity(chasis);
	avion->setModelMat(translate(dmat4(1), dvec3(0, radioOrbita, 0)));
	avion->setModelMat(scale(avion->modelMat(), glm::dvec3(0.2, 0.2, 0.2)));*/
	//this->addEntity(avion);

	addEntity(alas);
	addEntity(chasis);
	double compZ = radioOrbita * sin(radians(angle));
	double compY = radioOrbita * cos(radians(angle));
	setModelMat(translate(dmat4(1), dvec3(0, compY, compZ)));

	///Esto se hizo en la entrega de "Practica 2" se ha corregido 
	//setModelMat(rotate(mModelMat, glm::radians(angle), dvec3(1, 0, 0)));

	setModelMat(scale(modelMat(), dvec3(0.2, 0.2, 0.2)));


	luzFoco->setPosDir(fvec3(0, -30, 0));
	luzFoco->setSpot(fvec3(0.0f, -1, 0.0f), 30, 1);
}

void Avion::render(glm::dmat4 const& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
	glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	luzFoco->upload(aMat);
}

void Avion::move()
{
	///Esto se hizo en la entrega de "Practica 2" se ha corregido 
	//Rotamos el objeto desde el pivote del (0,0,0)
	//this->setModelMat(rotate(dmat4(1), glm::radians(angle), dvec3(1, 0, 0)));

	double compZ = radioOrbita * sin(radians(angle));
	double compY = radioOrbita * cos(radians(angle));
	setModelMat(translate(dmat4(1), dvec3(0, compY, compZ)));
	setModelMat(rotate(mModelMat, glm::radians(angle), dvec3(1, 0, 0)));
	setModelMat(scale(modelMat(), dvec3(0.2, 0.2, 0.2)));

	angle++;
	//Rotamos las hélices con un angulo de 10º
	helicesAvion->setModelMat(rotate(helicesAvion->modelMat(), radians(10.0), dvec3(0, 0, 1)));


	///Esto se hizo en la entrega de "Practica 2" se ha corregido 
	//Movemos la luz conforme al avión apuntando al origen
	// compY = radioOrbita * cos(radians(angle));
	// compZ = radioOrbita * sin(radians(angle));
	//luzFoco->setPosDir(fvec3(0, compY, compZ));
	//luzFoco->setSpot(fvec3(0.0f, -compY, -compZ), 30, 1);
}
