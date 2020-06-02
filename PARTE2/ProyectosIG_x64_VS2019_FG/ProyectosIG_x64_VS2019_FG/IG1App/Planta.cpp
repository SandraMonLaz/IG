#include "Planta.h"
using namespace glm;


void Planta::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//Color
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//Textura
		if (mTexture != nullptr)mTexture->bind(GL_REPLACE);
		mMesh->render();

		//Reseteamos los valores
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1.0);
		if (mTexture != nullptr)mTexture->unbind();
		glDisable(GL_ALPHA_TEST);
	}
}
