#include "Caja.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;


Caja::Caja(GLdouble ld , Texture* interna, GLdouble ofset) {
	mMesh = Mesh::generaCajaTexCor(ld);
	mModelMat = translate(dmat4(1), dvec3(-ofset, ld/2, -ofset));

	//Creamos el suelo y situamos la malla en la posición determonada
	suelo = Mesh::generaRectanguloTexCor(ld, ld, 1, 1);
	mModelMatSuelo = translate(dmat4(1), dvec3(-ofset, 0.1, -ofset));
	mModelMatSuelo = rotate(mModelMatSuelo, radians(90.0), dvec3(1, 0, 0));
	txtInterna = interna;
}


void Caja::render(glm::dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		//Color
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//Textura
		//--Text Externa
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		mMesh->render();
		//--Text Interna
		glCullFace(GL_FRONT);
		if (txtInterna != nullptr) txtInterna->bind(GL_REPLACE);
		mMesh->render();
	}
	if (suelo != nullptr) {
		dmat4 aMat = modelViewMat * mModelMatSuelo;  // glm matrix multiplication
		upload(aMat);
		//Color
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//Textura
		suelo->render();
	}
	//Reset
	glDisable(GL_CULL_FACE);
	if (mTexture != nullptr) mTexture->unbind();
	if (txtInterna != nullptr) txtInterna->unbind();

}
