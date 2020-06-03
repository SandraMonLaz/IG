#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
class Fondo    // EXTRA 1
{
public:
	Fondo() {
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
	void setSizeVP(double xw, double yh);
	void render();
	~Fondo();

private:
	Mesh* mMesh;
	Texture* textura;
	Texture* secondTexture;
	Camera* camera;

	Viewport* viewport;
};

