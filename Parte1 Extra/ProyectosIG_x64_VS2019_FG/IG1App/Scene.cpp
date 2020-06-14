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
#include "Cristalera.h"
#include <string>
#include "Planta.h"

using namespace glm;
using namespace std;
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

		Texture* cristal = new Texture();
		cristal->load("../Bmps/windowV.bmp", 150);
		gTextures.push_back(cristal);

		Texture* planta = new Texture();
		planta->load("../Bmps/grass.bmp", glm::u8vec3{0,0,0},0);
		gTextures.push_back(planta);

		//---------------Objetos Escena---
		Caja* caja = new Caja(100,cuboInt,300);
		caja->setTexture(cuboExt);

		Estrella* estrella = new Estrella(8, 100, 100);
		estrella->setTexture(starText);
		estrella->changeColor(0.0, 1.0, 0.0, 1.0);

		Suelo* suelo = new Suelo(800, 800, 10.0, 10.0);
		suelo->setTexture(sueloT);
		
		Foto* foto = new Foto(100.0, 200.0);
		foto->setTexture(fotoT);

		Cristalera* cristalera = new Cristalera(800);
		cristalera->setTexture(cristal);

		Planta* p = new Planta(100, 100, 1, 1);
		p->setTexture(planta);
		p->setModelMat(rotate(p->modelMat(),radians(90.0),dvec3(0,1,0)));
		Planta* p2 =new Planta(100, 100, 1, 1);
		p2->setTexture(planta);

		gObjects.push_back(estrella);
		gObjects.push_back(caja);
		gObjects.push_back(suelo);
		gObjects.push_back(foto);
		gObjects.push_back(new EjesRGB(400.0));
		gObjectsTran.push_back(p);
		gObjectsTran.push_back(p2);
		gObjectsTran.push_back(cristalera);

	}
}

void Scene::setState(int id) {
	if (mId != id) {
		mId = id;
		free();
		gObjects.clear();
		gTextures.clear();
		gObjectsTran.clear();
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

	for (Abs_Entity* el : gObjectsTran) {
		delete el; el = nullptr;
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
	glEnable(GL_TEXTURE_2D);  // enable textures
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
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (Abs_Entity* el : gObjectsTran)
	{
		el->render(cam.viewMat());
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
void Scene::update() {
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}
void Scene::saveBMP(int texture) {
	string a = "../Bmps/Foto.bmp";
	gTextures[texture]->save(a);
}
//-------------------------------------------------------------------------


