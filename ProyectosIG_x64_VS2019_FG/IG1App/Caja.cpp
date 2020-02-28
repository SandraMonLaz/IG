#include "Caja.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;


Caja::Caja(GLdouble ld) {
	mMesh = Mesh::generaCajaTexCor(ld);
}


void Caja::render(glm::dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//Color
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(2);
		
		glEnable(GL_CULL_FACE);
		//Textura
		if (mTexture != nullptr)mTexture->bind(GL_REPLACE);
		glCullFace( GL_BACK);
		mMesh->render();
		if (mTexture != nullptr)mTexture->unbind();


		//Textura
		if (t != nullptr)t->bind(GL_REPLACE);
		glCullFace(GL_FRONT);
		mMesh->render();
		//Reset
		if (mTexture != nullptr)mTexture->unbind();

		//Reset
		glLineWidth(1);
		glDisable(GL_CULL_FACE);
	}

}