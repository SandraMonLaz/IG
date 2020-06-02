#pragma once
#include "Entity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
class RectanguloRGB : public Abs_Entity
{
public:
	RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity() { 
		mMesh = Mesh::generaRectanguloRGB(w, h);
	}
	~RectanguloRGB() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

