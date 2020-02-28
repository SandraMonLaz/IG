#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "Poligono.h"
#include "Sierpinski.h"
#include "TrianguloRGB.h"
#include "RectanguloRGB.h"
#include "Estrella.h"
#include "Caja.h"
#include "Suelo.h"
#include "Foto.h"

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

		Texture* sueloT = new Texture();
		sueloT->load("../Bmps/baldosaC.bmp");
		gTextures.push_back(sueloT);

		Texture* cuboExt = new Texture();
		cuboExt->load("../Bmps/container.bmp");
		gTextures.push_back(cuboExt);

		Texture* cuboInt = new Texture();
		cuboInt->load("../Bmps/papelE.bmp");
		gTextures.push_back(cuboInt);

		Texture* fotoT = new Texture();
		gTextures.push_back(fotoT);

		//---------------Objetos Escena---
		Caja* caja = new Caja(100,cuboInt,300);
		caja->setTexture(cuboExt);

		Estrella* estrella = new Estrella(4, 100, 100);
		estrella->setTexture(starText);
		estrella->changeColor(0.0, 1.0, 0.0, 1.0);

		Suelo* suelo = new Suelo(1000, 1000, 10.0, 10.0);
		suelo->setTexture(sueloT);
		
		Foto* foto = new Foto(100.0, 200.0);
		foto->setTexture(fotoT);

		gObjects.push_back(estrella);
		gObjects.push_back(caja);
		gObjects.push_back(suelo);
		gObjects.push_back(foto);
		gObjects.push_back(new EjesRGB(400.0));
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


