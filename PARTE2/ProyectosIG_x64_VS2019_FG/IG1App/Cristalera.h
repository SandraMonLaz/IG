#pragma once
#include "Entity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

class Cristalera : public Abs_Entity
{
public:
	Cristalera(GLdouble ld) : Abs_Entity() { 
		mMesh = Mesh::generaCajaTexCor(ld);
		mModelMat = translate(dmat4(1), dvec3(0, ld/2, 0));
	};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

