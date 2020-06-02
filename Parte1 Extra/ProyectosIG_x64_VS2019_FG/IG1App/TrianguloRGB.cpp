#include "TrianguloRGB.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // por defecto
	}
}
void TrianguloRGB::update(){
	mModelMat = translate(dmat4(1), dvec3(rd * cos(radians(-angleC)), rd * sin(radians(-angleC)), 0));
	mModelMat = rotate(mModelMat, radians(angleT), dvec3(0, 0, 1));
	angleC += 1;//Angulo en torno a la circunferencia
	angleT += 2; //Angulo en torno a su propio centro
}