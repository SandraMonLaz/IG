#include "Planta.h"


void Planta:: render(glm::dmat4 const& modelViewMat) const {

	if (mMesh != nullptr) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_FILL);
		if (mTexture != nullptr)mTexture->bind(GL_REPLACE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // por defecto
		if (mTexture != nullptr)mTexture->unbind();
	}
 }
