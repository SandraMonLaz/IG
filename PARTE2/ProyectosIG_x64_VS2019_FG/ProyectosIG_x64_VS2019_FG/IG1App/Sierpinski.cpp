#include "Sierpinski.h"
#include <gtc\type_ptr.inl>

void Sierpinski::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPointSize(2);
		mMesh->render();
		glColor3b(1.0,1.0,1.0);
		glPointSize(1);
	}

}