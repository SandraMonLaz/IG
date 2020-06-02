#include "Fondo.h"
#include <gtc\type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

void Fondo::setSizeVP(double xw, double yh)
{	
	viewport->setSize(xw, yh);
}

void Fondo::render()
{
	camera->upload();
	if (mMesh != nullptr) {
		glDisable(GL_DEPTH_TEST);
		
		glPolygonMode(GL_FRONT, GL_FILL);
		//Textura
		if (textura != nullptr)textura->bind(GL_REPEAT);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (textura != nullptr)textura->unbind();
		glEnable(GL_DEPTH_TEST);
	}
}
