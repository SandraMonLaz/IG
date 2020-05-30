//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>
#include "Light.h"
#include "Avion.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	enum {
		starText, sueloT, cuboExt, cuboInt, fotoT, cristal
	};
	Scene() { mId = 0; luzDireccionalActivada = false; luzPosicionalActivada = false; luzFocalActivada = false; luzFocalAvionActivada = false; };
	~Scene() { 
		free(); resetGL(); 
	
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

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();
    void render(Camera const& cam) const;
	void update();
	void setState(int id);

	void saveBMP(int texture);
	void setLight(bool encendida, int id);
	void ApagarEscena();
	void move();


protected:
	int mId;
	void escena0();
	void escena1();
	void escena2();
	void escena3();
	void escena4();
	void escena5();
	void escena6();
	void escena7();
	void escena8();
	void sceneDirLight(Camera const& cam) const;
	void scenePosLight(Camera const& cam) const;
	void sceneSpotLight(Camera const& cam) const;
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gObjectsTran;  // Entities (graphic objects tran) of the scene
	std::vector<Texture*> gTextures;    
	bool luzDireccionalActivada;
	bool luzPosicionalActivada;
	bool luzFocalActivada;
	bool luzFocalAvionActivada;
	bool luzCamaraActivada;

	DirLight* directionalLight = nullptr;
	PosLight* positionalLight = nullptr;
	SpotLight* spotSceneLight = nullptr;
	SpotLight* planeLight = nullptr;
	PosLight* cameraLight = nullptr;
	Avion* avion = nullptr;

	void setLights();
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

