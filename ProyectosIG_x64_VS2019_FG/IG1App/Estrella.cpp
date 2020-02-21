#include "Estrella.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;



Estrella:: Estrella(int numPicos, double h, double re) : Abs_Entity() {
	mMesh = Mesh::generaEstrellaTexCor(re, numPicos, h);
	anguloY = 0;
	anguloZ = 0;
	mModelMat = translate(dmat4(1), dvec3(0, 150, 0));
}


void Estrella::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//Color
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(2.0);
		//Textura
		if(mTexture!=nullptr)mTexture->bind(GL_REPLACE);
		mMesh->render();

		//Duplicamos la malla
		dmat4 nueva =rotate(mModelMat,radians(180.0),dvec3(0,1,0));
		nueva = modelViewMat*nueva;
		upload(nueva);
		mMesh->render();

		//Reseteamos los valores
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1.0);
		if (mTexture != nullptr)mTexture->unbind();
	}
}

void Estrella::update() {

	mModelMat = translate(dmat4(1), dvec3(0, 150, 0));
	mModelMat = rotate(mModelMat,radians(anguloY),dvec3(0,1,0));
	anguloY++;
	mModelMat = rotate(mModelMat, radians(anguloZ),dvec3(0,0,1));
	anguloZ++;	
}