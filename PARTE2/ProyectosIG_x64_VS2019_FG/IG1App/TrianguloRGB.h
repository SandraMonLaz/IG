#pragma once
#include "Entity.h"
#include "Poligono.h"
class TrianguloRGB : public Abs_Entity
{
public:
	TrianguloRGB(GLdouble radioProp, GLdouble radioGiro) : Abs_Entity(), rd(radioGiro)  { mMesh = Mesh::generaTrianguloRGB(radioProp); };
	~TrianguloRGB() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	double angleC = 25.0,angleT=0.0, rd = 0;
};

