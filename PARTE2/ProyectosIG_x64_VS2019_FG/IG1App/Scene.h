//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	enum {
		starText, sueloT, cuboExt, cuboInt, fotoT, cristal
	};
	Scene() { mId = 0; luzDireccionalActivada = true; luzPosicionalActivada = false; luzFocalActivada = false; };
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();
    void render(Camera const& cam) const;
	void update();
	void setState(int id);

	void saveBMP(int texture);
	void setLuzDireccionalActivada(bool b) { luzDireccionalActivada = b; }
	void setLuzPosicionalActivada(bool b) { luzPosicionalActivada = b; }
	void setLuzFocalActivada(bool b) { luzFocalActivada = b; }
	void ApagarEscena();


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
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

