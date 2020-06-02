#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
class Fondo
{
public:
	Fondo() {
		//Inicializamos la textura
		textura = new Texture();
		textura->load("../Bmps/noche.bmp");
		//Inicializamos la malla
		mMesh = Mesh::generaRectanguloTexCor(2, 2, 1, 1);
		//Inicializamos el puerto de vista al tamaño de la ventana de la aplicación
		//con una ventana de vista de 2x2
		viewport = new Viewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		camera = new Camera(viewport);
		camera->set2D();
		camera->setSize(2, 2);
	}
	void setSizeVP(double xw, double yh);
	void render();
	~Fondo() { delete mMesh; delete textura; delete camera; }

private:
	Mesh* mMesh;
	Texture* textura;
	Camera* camera;

	Viewport* viewport;
};

