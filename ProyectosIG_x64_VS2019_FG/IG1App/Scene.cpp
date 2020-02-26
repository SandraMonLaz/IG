#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "Poligono.h"
#include "Sierpinski.h"
#include "TrianguloRGB.h"
#include "RectanguloRGB.h"
#include "Estrella.h"
#include "Planta.h"
#include "Caja.h"
#include "Cristalera.h"
#include "Suelo.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{
	setGL();  // OpenGL settings



	// allocate memory and load resources
	// Lights
	// Textures

	//Escena 2D
	if (mId == 0) {
		Poligono* cir = new Poligono(100, 200);
		Sierpinski* s = new Sierpinski(10000, 200);
		s->changeColor(1, 1, 0, 1);
		cir->changeColor(1, 0.3, 0.2, 1);
		TrianguloRGB* tRGB = new TrianguloRGB(50,200);
		RectanguloRGB* recRGB = new RectanguloRGB(1000, 1000);
		recRGB->setModelMat(translate(dmat4(1), dvec3(0, 0, -100)));
		gObjects.push_back(cir);
		gObjects.push_back(s);
		gObjects.push_back(tRGB);
		gObjects.push_back(recRGB);
	}

	//Escena 3D
	if (mId == 1) {
		//-------------Texturas-----------
		Texture* starText = new Texture();
		starText->load("../Bmps/baldosaP.bmp");
		gTextures.push_back(starText);

		Texture* cajaText = new Texture();
		cajaText->load("../Bmps/container.bmp");
		gTextures.push_back(cajaText);
		Texture* suelo = new Texture();
		suelo->load("../Bmps/baldosaC.bmp");
		gTextures.push_back(suelo);


		Texture* cajaInside = new Texture();
		cajaInside->load("../Bmps/papelE.bmp");
		gTextures.push_back(cajaInside);

		Texture* cristalera = new Texture();
		cristalera->load("../Bmps/windowV.bmp");
		gTextures.push_back(cristalera);

		Texture* hierba = new Texture();//grass
		hierba->load("../Bmps/grass.bmp");
		gTextures.push_back(hierba);

		//---------------Objetos Escena---
		Caja* c = new Caja(100);
		c->setTexture(cajaText);
		c->setTextInside(cajaInside);

		/*Cristalera* cris = new Cristalera(1000);
		cris->setTexture(cristalera);*/

		Estrella* e = new Estrella(4, 100, 100);
		e->setTexture(starText);
		e->changeColor(0.0, 1.0, 0.0, 1.0);
		Suelo* s = new Suelo(1000, 1000, 20.0, 20.0);
		s->setTexture(suelo);

		Planta* hierba1 = new Planta(100,100);
		hierba1->setTexture(hierba);
		hierba1->setModelMat(translate(hierba1->modelMat(),dvec3(350,100,0)));
		//RectanguloRGB* hierba2 = new RectanguloRGB(100, 100);
		

		gObjects.push_back(e);
		gObjects.push_back(c);
		gObjects.push_back(s);
		gObjects.push_back(new EjesRGB(400.0));
		gObjects.push_back(hierba1);
		//gObjects.push_back(cris);   //Mejor que esté al final para que se vea a través de él todos los objetos
	}
}

void Scene::setState(int id) {
	if (mId != id) {
		mId = id;
		free();
		gObjects.clear();
		gTextures.clear();
		init();
	}
}


//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}

	for (Texture* el : gTextures)
	{
		delete el;  el = nullptr;
	}

}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // disable textures

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);  // disable textures
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());
	}
}
void Scene::update() {
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------


