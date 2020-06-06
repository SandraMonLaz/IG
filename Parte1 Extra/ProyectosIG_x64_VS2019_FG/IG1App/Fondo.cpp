#include "Fondo.h"
#include <gtc\type_ptr.hpp>
#include <gtc/matrix_transform.hpp>


Fondo::Fondo() {

	//Inicializamos la textura
	textura = new Texture();
	secondTexture = new Texture();
	textura->load("../Bmps/noche.bmp");
	secondTexture->load("../Bmps/Zelda.bmp", 50);
	//Inicializamos la malla
	mMesh = Mesh::generaRectanguloTexCor(2, 2, 1, 1);
	mMesh->setTwoUnits();
	//Inicializamos el puerto de vista al tamaño de la ventana de la aplicación
	//con una ventana de vista de 2x2
	viewport = new Viewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	camera = new Camera(viewport);
	camera->set2D();
	camera->setSize(2, 2);
}



void Fondo::setSizeVP(double xw, double yh)
{
	viewport->setSize(xw, yh);
}

void Fondo::render()
{
	glDisable(GL_DEPTH_TEST);
	camera->upload();

	glPolygonMode(GL_FRONT, GL_FILL);
	//Para que solo se renderice la cara frontal del fondo
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//if (textura != nullptr) textura->bind(GL_REPLACE);						// EXTRA 1
	//Textura
	if (textura != nullptr)textura->bind(GL_DECAL, GL_TEXTURE0);				// EXTRA 2
	if (secondTexture != nullptr)secondTexture->bind(GL_DECAL, GL_TEXTURE1);    // EXTRA 2

	mMesh->render();

	if (textura != nullptr)textura->unbind(GL_TEXTURE0);					    // EXTRA 1
	if (secondTexture != nullptr)secondTexture->unbind(GL_TEXTURE1);			// EXTRA 2

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

}

Fondo::~Fondo()
{
	delete mMesh; mMesh = nullptr;
	delete textura; textura = nullptr;
	delete camera; camera = nullptr;
	delete secondTexture;  secondTexture = nullptr;
	delete viewport; viewport = nullptr;
}
