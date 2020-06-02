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
	Scene() { mId = 0; };
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();
    void render(Camera const& cam) const;
	void update();
	void setState(int id);

	void saveBMP(int texture);
protected:
	int mId;
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gObjectsTran;  // Entities (graphic objects tran) of the scene
	std::vector<Texture*> gTextures;    
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

