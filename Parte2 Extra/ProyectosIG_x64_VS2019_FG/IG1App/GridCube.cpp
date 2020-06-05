#include "GridCube.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

GridCube::GridCube(Texture* arribaT, Texture* lateral)
{
	Grid* arriba = new Grid(200,10);
	arriba->setModelMat(glm::translate(glm::dmat4(1), glm::dvec3(0,100,0)));
	arriba->setTexture(arribaT);
	Grid* abajo = new Grid(200, 10);
	abajo->setModelMat(glm::translate(glm::dmat4(1), glm::dvec3(0, -100, 0)));
	abajo->setModelMat(glm::rotate(abajo->modelMat(), glm::radians(180.0), glm::dvec3(1, 0, 0)));
	abajo->setTexture(arribaT);

	Grid* ladoX1 = new Grid(200, 10);
	ladoX1->setModelMat(glm::rotate(glm::dmat4(1), glm::radians(-90.0), glm::dvec3(0, 0, 1)));
	ladoX1->setModelMat(glm::translate(ladoX1->modelMat(), glm::dvec3(0, 100, 0)));
	ladoX1->setTexture(lateral);

	Grid* ladoX2 = new Grid(200, 10);
	ladoX2->setModelMat(glm::rotate(glm::dmat4(1), glm::radians(90.0), glm::dvec3(0, 0, 1)));
	ladoX2->setModelMat(glm::translate(ladoX2->modelMat(), glm::dvec3(0, 100, 0)));
	ladoX2->setTexture(lateral);

	Grid* ladoZ1 = new Grid(200, 10);
	ladoZ1->setModelMat(glm::rotate(glm::dmat4(1), glm::radians(90.0), glm::dvec3(0, 0, 1)));
	ladoZ1->setModelMat(glm::rotate(ladoZ1->modelMat(), glm::radians(-90.0), glm::dvec3(1, 0, 0)));
	ladoZ1->setModelMat(glm::translate(ladoZ1->modelMat(), glm::dvec3(0, 100, 0)));
	ladoZ1->setTexture(lateral);

	Grid* ladoZ2 = new Grid(200, 10);
	ladoZ2->setModelMat(glm::rotate(glm::dmat4(1), glm::radians(90.0), glm::dvec3(0, 0, 1)));
	ladoZ2->setModelMat(glm::rotate(ladoZ2->modelMat(), glm::radians(90.0), glm::dvec3(1, 0, 0)));
	ladoZ2->setModelMat(glm::translate(ladoZ2->modelMat(), glm::dvec3(0, 100, 0)));
	ladoZ2->setTexture(lateral);

	addEntity(arriba);
	addEntity(abajo);
	addEntity(ladoX1);
	addEntity(ladoX2);
	addEntity(ladoZ1);
	addEntity(ladoZ2);


}
