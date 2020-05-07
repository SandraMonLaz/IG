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
#include "QuadricEntity.h"
#include "AnilloCuadrado.h"
#include "EntityWithIndexMesh.h"

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
		escena0();
	}
	//Escena 3D
	else if (mId == 1) {
		escena1();
	}
	else if (mId == 2) {
		escena2();
	}
	else if (mId == 3)
		escena3();
	else if (mId == 4)
		escena4();
}
void Scene::escena0() {
	Poligono* cir = new Poligono(100, 200);
	Sierpinski* s = new Sierpinski(10000, 200);
	s->changeColor(1, 1, 0, 1);
	cir->changeColor(1, 0.3, 0.2, 1);
	TrianguloRGB* tRGB = new TrianguloRGB(50, 200);
	RectanguloRGB* recRGB = new RectanguloRGB(1000, 1000);
	recRGB->setModelMat(translate(dmat4(1), dvec3(0, 0, -100)));
	gObjects.push_back(cir);
	gObjects.push_back(s);
	gObjects.push_back(tRGB);
	gObjects.push_back(recRGB);
}
void Scene::escena1() {
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
	planta->load("../Bmps/grass.bmp", glm::u8vec3{ 0,0,0 }, 0);
	gTextures.push_back(planta);

	//---------------Objetos Escena---
	Caja* caja = new Caja(100, cuboInt, 300);
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
	p->setModelMat(rotate(p->modelMat(), radians(90.0), dvec3(0, 1, 0)));
	Planta* p2 = new Planta(100, 100, 1, 1);
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
void Scene::escena2() {
	Sphere* sphere = new Sphere(200);
	sphere->setColor(glm::fvec3(210.0f/255.0f, 105.0f/255.0f, 30.0f/255.0f));

	Cylinder* eyeL = new Cylinder(20, 0, 50);
	eyeL->setColor(glm::fvec3(0, 1, 1));
	eyeL->setModelMat(translate(glm::dmat4(1), dvec3(160, 80, 80)));
	eyeL->setModelMat(rotate(eyeL->modelMat(), radians(60.0), dvec3(0, 1, 0)));

	Cylinder* eyeR = new Cylinder(20, 0, 50);
	eyeR->setColor(glm::fvec3(32.0f/255.0f, 178.0f/255.0f, 170.0f/255.0f));
	eyeR->setModelMat(translate(glm::dmat4(1), dvec3(80, 80, 160)));
	eyeR->setModelMat(rotate(eyeR->modelMat(), radians(30.0), dvec3(0, 1, 0)));

	Disk* hat = new Disk(120, 200, 60);
	hat->setColor(glm::fvec3(100, 1, 0));
	hat->setModelMat(translate(glm::dmat4(1), dvec3(0, 150, 0)));
	hat->setModelMat(rotate(hat->modelMat(), radians(90.0), dvec3(1, 0, 0)));

	PartialDisk* smile = new PartialDisk(120, 140, 90, 180, 10);
	smile->setColor(glm::fvec3(0.0f, 1.0f, 0.0f));
	smile->setModelMat(translate(glm::dmat4(1), dvec3(110, 0, 110)));
	smile->setModelMat(rotate(smile->modelMat(), radians(45.0), dvec3(0, 1, 0)));
	// Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(sphere);
	gObjects.push_back(eyeL);
	gObjects.push_back(eyeR);
	gObjects.push_back(hat);
	gObjects.push_back(smile);
}

void Scene::escena3() {
	AnilloCuadrado* c = new AnilloCuadrado();
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(c);
}

void Scene::escena4()
{
	EntityWithIndexMesh* c = new EntityWithIndexMesh();
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(c);
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

void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
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
	if (mId == 2 || mId==3 || mId == 4)	glClearColor(0.7, 0.8, 0.9, 0.0);  // background color (alpha=1 -> opaque)
	else glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // disable textures
	glEnable(GL_COLOR_MATERIAL);
}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	 glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);  // disable textures
	glDisable(GL_COLOR_MATERIAL);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const
{
	cam.upload();
	if(mId > 1)sceneDirLight(cam);
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


