#include "Estrella.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;



Estrella:: Estrella(int numPicos, double h, double re) : Abs_Entity() {
	mMesh = Mesh::generaEstrella3D(re, numPicos, h);
	anguloY = 0;
	anguloZ = 0;
}


void Estrella::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.0);
		mMesh->render();

		dmat4 nueva =rotate(mModelMat,radians(180.0),dvec3(0,1,0));
		nueva = modelViewMat*nueva;
		upload(nueva);
		mMesh->render();

		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1.0);
	}
}

void Estrella::update() {

	mModelMat = rotate(dmat4(1),radians(anguloY),dvec3(0,1,0));
	anguloY++;
	mModelMat = rotate(mModelMat, radians(anguloZ),dvec3(0,0,1));
	anguloZ++;	
}