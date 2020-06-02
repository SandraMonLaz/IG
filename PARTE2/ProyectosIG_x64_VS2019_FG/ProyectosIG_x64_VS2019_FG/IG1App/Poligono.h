#pragma once
#include "Entity.h"
using namespace glm;
class Poligono : public Abs_Entity {
public:
	Poligono(GLuint numL, GLdouble rd) : Abs_Entity() { mMesh = Mesh::generaPoligono(numL, rd); };
	~Poligono() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

