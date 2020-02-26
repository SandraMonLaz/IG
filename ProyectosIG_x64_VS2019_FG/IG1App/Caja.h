#pragma once
#include "Entity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
class Caja :
	public Abs_Entity
{
	Texture* t;
	Mesh* suelo;
	dmat4 matSuelo;
public:
	Caja(GLdouble ld);
	void setTextInside(Texture* text) { t = text; }
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

