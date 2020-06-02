#pragma once
#include "Entity.h"
class Sierpinski :	public Abs_Entity
{
public:
	Sierpinski(GLuint numV, GLdouble rd) : Abs_Entity() { mMesh = Mesh::generaSierpinski(rd,numV); };
	~Sierpinski() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

