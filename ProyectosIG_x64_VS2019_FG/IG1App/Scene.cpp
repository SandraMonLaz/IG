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
		Caja* c = new Caja(100);
		Estrella* e = new Estrella(6, 200, 200.0);
		e->changeColor(0.0, 1.0, 0.0, 1.0);
		gObjects.push_back(e);
		gObjects.push_back(c);
		gObjects.push_back(new EjesRGB(400.0));
	}
}

void Scene::setState(int id) {
	if (mId != id) {
		mId = id;
		free();
		gObjects.clear();
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
}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
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


