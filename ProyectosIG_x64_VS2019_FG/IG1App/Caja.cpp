#include "Caja.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;


Caja::Caja(GLdouble ld) {
	mMesh = Mesh::generaCajaTexCor(ld);
	suelo = Mesh::generaRectanguloTexCor(ld,ld,1,1);
	matSuelo = translate(dmat4(1), dvec3(0, -ld / 2, 0));
	matSuelo = rotate(matSuelo,radians(90.0),dvec3(1,0,0));
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
		if (t != nullptr)t->unbind();

		//Reset
		glDisable(GL_CULL_FACE);
	}
	if (suelo != nullptr) {
		dmat4 aMat = modelViewMat * matSuelo;  // glm matrix multiplication
		upload(aMat);
		suelo->render();
	}
		glLineWidth(1);

}