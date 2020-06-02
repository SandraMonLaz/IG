#pragma once
#include "Entity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
using namespace glm;

class Foto : public Abs_Entity
{
public:
	Foto(GLdouble w, GLdouble h) : Abs_Entity()
	{
		mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
		mModelMat = translate(dmat4(1), dvec3(0, 0.1, 0));
		mModelMat = rotate(mModelMat, radians(90.0), dvec3(1, 0, 0));
	}
	~Foto() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

