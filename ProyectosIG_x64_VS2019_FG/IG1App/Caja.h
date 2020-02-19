#pragma once
#include "Entity.h"
class Caja :
	public Abs_Entity
{
public:
	Caja(GLdouble ld);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

