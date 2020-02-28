#pragma once
#include "Entity.h"
class Caja :
	public Abs_Entity
{
	Texture* t;
public:
	Caja(GLdouble ld);
	void setTextInside(Texture* text) { t = text; }
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

