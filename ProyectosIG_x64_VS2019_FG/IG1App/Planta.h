#pragma once
#include "Entity.h"
class Planta :
	public Abs_Entity
{


	public:
	Planta(GLdouble w, GLdouble h) : Abs_Entity() {
		mMesh = Mesh::generaRectanguloTexCor(w,h,1,1);
	}
	~Planta() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

