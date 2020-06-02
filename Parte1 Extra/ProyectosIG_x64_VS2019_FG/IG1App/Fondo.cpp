#include "Fondo.h"
#include <gtc\type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

void Fondo::setSizeVP(double xw, double yh)
{
	viewport->setSize(xw, yh);
}

void Fondo::render()
{
	glDisable(GL_DEPTH_TEST);
	camera->upload();

	glPolygonMode(GL_FRONT, GL_FILL);
	//Textura
	if (textura != nullptr)textura->bind(GL_REPLACE);
	mMesh->render();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (textura != nullptr)textura->unbind();
	glEnable(GL_DEPTH_TEST);

}
