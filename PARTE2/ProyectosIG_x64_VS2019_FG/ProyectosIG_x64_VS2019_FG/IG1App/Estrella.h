#pragma once
#include "Entity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
class Estrella : public Abs_Entity
{
	double anguloY;
	double anguloZ;
public:
	Estrella(int numPicos, double h, double re);
	~Estrella() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

