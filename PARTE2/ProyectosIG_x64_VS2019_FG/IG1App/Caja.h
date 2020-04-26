#pragma once
#include "Entity.h"
class Caja : public Abs_Entity
{
private:
	Mesh* suelo = nullptr;   // la malla del suelo
	glm::dmat4 mModelMatSuelo;    // modeling matrix
	Texture* txtInterna = nullptr;
public:
	Caja(GLdouble ld, Texture* interna, GLdouble ofset);
	~Caja() { delete suelo;  }
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

