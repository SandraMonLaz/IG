#pragma once
#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
class Suelo : public Abs_Entity
{
public:
	Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Abs_Entity() 
	{
		mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
		mModelMat = rotate(dmat4(1), radians(90.0), dvec3(1,0,0));
	}
	~Suelo() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

