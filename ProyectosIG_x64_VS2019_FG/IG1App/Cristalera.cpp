#include "Cristalera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;


Cristalera::Cristalera(GLdouble ld) {
	mMesh = Mesh::generaCajaTexCor(ld);
	setModelMat(translate(mModelMat,dvec3(0,ld/2,0)));
}


void Cristalera::render(glm::dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//Color
		glEnable(GL_BLEND);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(2);
		glBlendFunc(1, 1);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Textura
		if (mTexture != nullptr)mTexture->bind(GL_REPLACE);
		mMesh->render();
		if (mTexture != nullptr)mTexture->unbind();
		//Reset
		glLineWidth(1);
		glBlendFunc(1, 0);
		glDisable(GL_BLEND);
	}

}