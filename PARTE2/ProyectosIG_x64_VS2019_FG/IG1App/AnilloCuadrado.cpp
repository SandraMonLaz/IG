#include "AnilloCuadrado.h"

AnilloCuadrado::AnilloCuadrado() :Abs_Entity()
{
	mMesh = Mesh::generaAnilloCuadrado();
	
}

void AnilloCuadrado::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mMesh->render();
	}
}
