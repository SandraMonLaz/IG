#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "QuadricEntity.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

	Sphere* sphere = new Sphere(200);
	sphere->setColor(glm::fvec3(1, 1, 1));

	Cylinder* eyeL = new Cylinder(20, 0, 50);
	eyeL->setColor(glm::fvec3(0, 1, 1));
	eyeL->setModelMat(translate(glm::dmat4(1), dvec3(160, 80, 80)));
	eyeL->setModelMat(rotate(eyeL->modelMat(), radians(60.0), dvec3(0,1,0)));

	Cylinder* eyeR = new Cylinder(20, 0, 50);
	eyeR->setColor(glm::fvec3(0, 1, 1));
	eyeR->setModelMat(translate(glm::dmat4(1), dvec3(80, 80, 160)));
	eyeR->setModelMat(rotate(eyeR->modelMat(), radians(30.0), dvec3(0, 1, 0)));

	Disk* hat = new Disk(120, 200, 60);
	hat->setColor(glm::fvec3(100, 1, 0));
	hat->setModelMat(translate(glm::dmat4(1), dvec3(0, 150, 0)));
	hat->setModelMat(rotate(hat->modelMat(), radians(90.0), dvec3(1, 0, 0)));

	PartialDisk* smile = new PartialDisk(120, 140, 90, 180, 10);
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
	glClearColor(0.7, 0.8, 0.9, 1);  // background color (alpha=1 -> opaque)
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
	sceneDirLight(cam);
	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------
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

