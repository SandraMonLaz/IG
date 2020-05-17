#include "CompoundEntity.h"

CompoundEntity::~CompoundEntity()
{
	for (auto &go : gObjects) {
		delete go;
	}
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	for (auto& go : gObjects) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		go->render(aMat);
		
	}
}
