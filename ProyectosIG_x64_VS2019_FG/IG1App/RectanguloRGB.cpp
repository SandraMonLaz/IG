#include "RectanguloRGB.h"

using namespace glm;

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		mTexture->bind(GL_REPLACE);
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // por defecto
		mTexture->unbind();

	}
}
