#include "Poligono.h"
void Poligono::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(4);
		mMesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1.0);
	}

}