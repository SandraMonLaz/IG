#pragma once
#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
using namespace glm;

class Planta :	public Abs_Entity {
public:
	Planta(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Abs_Entity()
	{
		mModelMat = translate(dmat4(1), dvec3(200,h/2,-200));
		mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	}
	~Planta() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

