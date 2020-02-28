#include "Caja.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;


Caja::Caja(GLdouble ld) {
	mMesh = Mesh::generaContCubo(ld);
}


void Caja::render(glm::dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		//Color
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
		//Textura
		//mTexture->bind(GL_REPLACE);

		mMesh->render();
		//Reset
		//mTexture->unbind();
		glLineWidth(1);
	}

}