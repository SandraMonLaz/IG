#pragma once
#include "Entity.h"
class AnilloCuadrado : public Abs_Entity	
{
public:
	AnilloCuadrado();
	~AnilloCuadrado() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
private:

};

