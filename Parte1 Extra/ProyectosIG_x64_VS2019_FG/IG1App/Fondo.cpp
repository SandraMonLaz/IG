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

	//if (textura != nullptr) textura->bind(GL_REPLACE);						// EXTRA 1
	//Textura
	if (textura != nullptr)textura->bind(GL_DECAL, GL_TEXTURE0);				// EXTRA 2
	if (secondTexture != nullptr)secondTexture->bind(GL_DECAL, GL_TEXTURE1);    // EXTRA 2

	mMesh->render();	

	if (textura != nullptr)textura->unbind(GL_TEXTURE0);					    // EXTRA 1
	if (secondTexture != nullptr)secondTexture->unbind(GL_TEXTURE1);			// EXTRA 2

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

}

Fondo::~Fondo()
{
	delete mMesh; mMesh = nullptr;
	delete textura; textura = nullptr;
	delete camera; camera = nullptr;
	delete secondTexture;  secondTexture = nullptr;
}
