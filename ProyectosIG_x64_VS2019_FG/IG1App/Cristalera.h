#pragma once
#include "Entity.h"
class Cristalera :
	public Abs_Entity
{

public:
	Cristalera(GLdouble ld);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

