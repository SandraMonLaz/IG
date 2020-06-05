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
#include "CompoundEntity.h"
#include "EntityWithMaterial.h"
#include "GridCube.h"

using namespace glm;
using namespace std;
//-------------------------------------------------------------------------

Scene::Scene() {
	 mId = 9; 
	 //////////////////LUCES///////////////////////////////////
	 luzDireccionalActivada = false;  directionalLight = nullptr;
	 luzPosicionalActivada = false;   positionalLight = nullptr;
	 luzFocalActivada = false;        spotSceneLight = nullptr;
	 luzFocalAvionActivada = false;   planeLight = nullptr;
	 luzCamaraActivada = false;       cameraLight = nullptr;
	 luzSirenaActivada = false;       sirenLight = nullptr;

	 radioOrbita = 150;
	 avion = nullptr;
	 sirenCube = nullptr;
}

Scene::~Scene() {
	free(); resetGL();

	////////////////////////////Desactivo/Destruyo las luces /////////////
	if (positionalLight != nullptr) delete positionalLight;
	if (spotSceneLight != nullptr) delete spotSceneLight;
	if (directionalLight != nullptr) delete directionalLight;
	if (planeLight != nullptr) delete planeLight;
	if (cameraLight != nullptr) delete cameraLight;

	positionalLight = nullptr;
	spotSceneLight = nullptr;
	directionalLight = nullptr;
	planeLight = nullptr;
	cameraLight = nullptr;
};

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
	else if (mId == 5)
		escena5();
	else if (mId == 6)
		escena6();
	else if (mId == 7)
		escena7();
	else if (mId == 8)
		escenaGrid();
	else if (mId == 9)
		escenaSirenCube();
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

//Cubo Rojo
void Scene::escena4()
{
	Cubo* c = new Cubo(glm::dvec4(1.0f,0.0f,0.0f,1.0f));
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(c);
}
//Avion
void Scene::escena5()
{
	//Helices---------------------------------------
	Cylinder* heliceIzq = new Cylinder(200,100,400);
	heliceIzq->setColor(glm::fvec3(0.0f,0.0f,1.0f));
	heliceIzq->setModelMat(rotate(dmat4(1), radians(90.0), dvec3(0, 1, 0)));

	Cylinder* heliceDcha = new Cylinder(200,100,400);
	heliceDcha->setColor(glm::fvec3(0.0f, 0.0f, 1.0f));
	heliceDcha->setModelMat(rotate(dmat4(1), radians(-90.0), dvec3(0, 1, 0)));

	CompoundEntity* helices = new CompoundEntity();
	helices->addEntity(heliceDcha);
	helices->addEntity(heliceIzq);
	helices->setModelMat(translate(glm::dmat4(1), dvec3(0, 0, 230)));
	helices->setModelMat(scale(helices->modelMat(), glm::dvec3(0.3, 0.2, 0.2)));
	//Chasis---------------------------------------
	Sphere* bola = new Sphere(200);
	bola->setColor(glm::fvec3(1.0f, 0.0f, 0.0f));
	CompoundEntity* chasis = new CompoundEntity();
	chasis->addEntity(bola);
	chasis->addEntity(helices);
	//Alas---------------------------------------
	Cubo* alas = new Cubo(glm::dvec4(0.0f, 1.0f, 0.0f, 1.0f));
	alas->setModelMat(scale(glm::dmat4(1), glm::dvec3(8, 0.4, 2)));
	CompoundEntity* avion = new CompoundEntity();
	avion->addEntity(alas);
	avion->addEntity(chasis);

	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(avion);
}
//Cono

//Esferas
void Scene::escena6()
{
	Esfera* esfera = new Esfera(20, 200, 20, glm::dvec4(0.0f, 0.0f, 1.0f, 1.0f));
	esfera->setModelMat(translate(glm::dmat4(1), dvec3(0, 0,400)));
	Sphere* sphere = new Sphere(200);
	sphere->setColor(glm::fvec3(0.0f, 0.0f, 1.0f));
	sphere->setModelMat(translate(glm::dmat4(1), dvec3(400, 0, 0)));
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(esfera);
	gObjects.push_back(sphere);
}

//Escena Planeta/Avion
void Scene::escena7()
{

	int radioEsfera = 150;
	avion = new Avion(radioEsfera+60, planeLight);
	Esfera* esfera = new Esfera(120, radioEsfera, 120, glm::dvec4(127.0f / 255.0f, 1.0f, 212.0f / 255.0f, 1.0f));

	/////////////////////////Para que esté con matrial y color dorado///////////////////////////////
	//esfera->setGold(); 
	/////////////////////////////////////

	//////////////////////////Para que este con material y color azul//////////////////////////////
	Material* m = new Material();
	m->setGold();
	////////////////////////////
	esfera->setMaterial(m); 
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(avion);
	gObjects.push_back(esfera);
}

void Scene::escenaGrid()
{

	Texture* gridtext = new Texture();
	gridtext->load("../Bmps/checker.bmp");
	gTextures.push_back(gridtext);

	Texture* gridWall = new Texture();
	gridWall->load("../Bmps/stones.bmp");
	gTextures.push_back(gridWall);
	GridCube* g = new GridCube(gridtext,gridWall);
	//Grid* g = new Grid(200, 10);
	//g->setTexture(gridtext);
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(g);

}

void Scene::escenaSirenCube()
{
	Texture* gridtext = new Texture();
	gridtext->load("../Bmps/checker.bmp");
	gTextures.push_back(gridtext);

	Texture* gridWall = new Texture();
	gridWall->load("../Bmps/stones.bmp");
	gTextures.push_back(gridWall);

	//Planeta
	Esfera* esfera = new Esfera(120, radioOrbita , 120, glm::dvec4(127.0f / 255.0f, 1.0f, 212.0f / 255.0f, 1.0f));

	sirenCube = new SirenCube(gridtext,gridWall, radioOrbita +30, sirenLight);
	gObjects.push_back(sirenCube);
	gObjects.push_back(esfera);
	gObjects.push_back(new EjesRGB(400.0));

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
	if (luzDireccionalActivada) {
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
	else {
		glDisable(GL_LIGHT0);
	}
}
void Scene::scenePosLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	if (luzPosicionalActivada) {
		glEnable(GL_LIGHT1);
		glm::fvec4 posDir = { 500, 500, 0, 1 };
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(cam.viewMat()));
		glLightfv(GL_LIGHT1, GL_POSITION, value_ptr(posDir));
		glm::fvec4 ambient = { 0, 0, 0, 1 };
		glm::fvec4 diffuse = { 0.5, 1, 0, 1 };
		glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT1, GL_AMBIENT, value_ptr(ambient));
		glLightfv(GL_LIGHT1, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(GL_LIGHT1, GL_SPECULAR, value_ptr(specular));
	}
	else {
		glDisable(GL_LIGHT1);
	}
}

//Focal
void Scene::sceneSpotLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	if (luzFocalActivada) {
		glEnable(GL_LIGHT2);
		glm::fvec4 posDir = { 0, 0,220, 1 };
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(cam.viewMat()));
		//glShadeModel(GL_SMOOTH);
		glLightfv(GL_LIGHT2, GL_POSITION, value_ptr(posDir));
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.0);
		glm::fvec3  dir = { 0.0, 0.0, -1.0 };
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, value_ptr(dir));

		glm::fvec4 ambient = { 0, 0, 0, 1 };
		glm::fvec4 diffuse = { 1, 2, 0, 1 };
		glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, value_ptr(ambient));
		glLightfv(GL_LIGHT2, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(GL_LIGHT2, GL_SPECULAR, value_ptr(specular));

	}
	else {
		glDisable(GL_LIGHT2);
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
	if (mId > 1) {
		glClearColor(0.7, 0.8, 0.9, 0.0);  // background color (alpha=1 -> opaque)
		setLights();
	}
	else {
		//Para que las escenas que no tienen luz no se vean mal ni raro
		glDisable(GL_LIGHTING);
		glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	}
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // disable textures
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);  // disable textures
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
}
void Scene::setLights()
{
	glEnable(GL_LIGHTING);
	//Luz direccional
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	if (directionalLight == nullptr) directionalLight = new DirLight();
	directionalLight->setPosDir(posDir);
	directionalLight->setAmb(ambient);
	directionalLight->setDiff(diffuse);
	directionalLight->setSpecular(specular);
	luzDireccionalActivada = true;

	//Estas dos luces las ponemos en Disable para que solo se vea la primera
	//Luz posicional
	posDir = { 500, 500, 0, 1 };
	ambient = { 0, 0, 0, 1 };
	diffuse = { 0.5, 1, 0, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };
	if (positionalLight == nullptr) positionalLight = new PosLight();
	positionalLight->setPosDir(posDir);
	positionalLight->setAmb(ambient);
	positionalLight->setDiff(diffuse);
	positionalLight->setSpecular(specular);
	positionalLight->disable();
	luzPosicionalActivada = false;

	//Luz focal
	posDir = { 0, 0,300, 1 };
	glm::fvec3  dir = { 0.0, 0.0, -1.0 };

	ambient = { 0, 0, 0, 1 };
	diffuse = { 1, 1, 1, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };
	if (spotSceneLight == nullptr) spotSceneLight = new SpotLight(posDir);
	spotSceneLight->setAmb(ambient);
	spotSceneLight->setDiff(diffuse);
	spotSceneLight->setSpecular(specular);
	spotSceneLight->setSpot(dir, 20, 0);
	spotSceneLight->disable();
	luzFocalActivada = false;

	//Luz focal avion
	posDir = { 0, 160,0, 1 };
	dir = { 0.0, -1.0, 0.0 };

	ambient = { 0, 0, 0, 1 };
	diffuse = { 1, 1, 1, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };
	if (planeLight == nullptr) planeLight = new SpotLight(posDir);
	planeLight->setAmb(ambient);
	planeLight->setDiff(diffuse);
	planeLight->setSpecular(specular);
	planeLight->setSpot(dir, 20, 1);
	planeLight->disable();
	luzFocalAvionActivada = false;

	//Camera
	posDir = { 500, 500, 0, 1 };
	ambient = { 0, 0, 0, 1 };
	diffuse = { 1, 1, 1, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };
	if (cameraLight == nullptr) cameraLight = new PosLight();
	cameraLight->setPosDir(posDir);
	cameraLight->setAmb(ambient);
	cameraLight->setDiff(diffuse);
	cameraLight->setSpecular(specular);
	cameraLight->disable();
	luzCamaraActivada = false;

	//LuzSirena
	posDir = { 0, radioOrbita+70,0, 1 };
	dir = { 0.0, -1.0,0.3 };

	ambient = { 0, 0, 0, 1 };
	diffuse = { 1, 1, 1, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };
	if (sirenLight == nullptr) sirenLight = new SpotLight(posDir);
	sirenLight->setAmb(ambient);
	sirenLight->setDiff(diffuse);
	sirenLight->setSpecular(specular);
	sirenLight->setSpot(dir, 20, 0);
	sirenLight->disable();
	luzSirenaActivada = false;
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const
{
	cam.upload();
	if (mId > 1) {
		if (luzDireccionalActivada) directionalLight->upload(cam.viewMat());
		if (luzFocalActivada) spotSceneLight->upload(cam.viewMat());
		if (luzPosicionalActivada)positionalLight->upload(cam.viewMat());
		if (luzFocalAvionActivada)planeLight->upload(cam.viewMat());
		if (luzCamaraActivada)cameraLight->upload(dmat4(1.0));
	}
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
	if(texture < gTextures.size() && gTextures[texture]!=nullptr)
		gTextures[texture]->save(a);
}
// - encendida = bool que nos indica si queremos que la luz esté activada
// - id = luz a la que quieres hacer referencia  para activar o desactivar
void Scene::setLight(bool encendida, int id)
{
	//Tomo la luz cuyo ID corresponda al que me hayan mandado y la activo/desactivo
	Light* l =  nullptr;
	switch (id)
	{
		case 0: l = directionalLight; luzDireccionalActivada = encendida; break;
		case 1: l = positionalLight; luzPosicionalActivada = encendida; break;
		case 2: l = spotSceneLight; luzFocalActivada = encendida; break;
		case 3: l = planeLight; luzFocalAvionActivada = encendida; break;
		case 4: l = cameraLight; luzCamaraActivada = encendida; break;
		case 5: l = sirenLight; luzSirenaActivada = encendida; break;
		default:break;
	}
	if (l != nullptr) {
		if (encendida) l->enable();
		else l->disable();	
	}
}
void Scene::ApagarEscena()
{
	if (mId > 1) {

		//Se desactivan todas las luces si 
		static bool encendido = true;
		if (encendido) {
			luzDireccionalActivada = false;
			luzPosicionalActivada = false;
			luzFocalActivada = false;
			luzCamaraActivada = false;
			luzFocalAvionActivada = false;
			encendido = false;
			//Ponemos ambient en negro
			GLfloat amb[] = { 0,0,0,1.0 };
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
			directionalLight->disable();
			positionalLight->disable();
			spotSceneLight->disable();
			planeLight->disable();
			cameraLight->disable();
		}
		//Se activa solo la luz direccional
		else {
			encendido = true;
			GLfloat amb[] = { 0.2,0.2,0.2,1.0 };
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
			luzDireccionalActivada = true;
			directionalLight->enable();
		}
	}
}
void Scene::move()
{
	//Le aviso al avion para que se mueva y modifique su foco
	if (avion != nullptr) avion->move();
}
//-------------------------------------------------------------------------

void Scene::sirenMove()
{
	//Le aviso al avion para que se mueva y modifique su foco
	if (sirenCube != nullptr) sirenCube->move();

}