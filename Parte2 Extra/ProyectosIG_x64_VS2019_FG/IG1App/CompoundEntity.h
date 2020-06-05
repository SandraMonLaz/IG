#pragma once
#include "Entity.h"
class CompoundEntity :	public Abs_Entity
{
public:
	CompoundEntity() :Abs_Entity() {};
	~CompoundEntity();
	void addEntity(Abs_Entity* ae) { gObjects.push_back(ae); }
	void render(glm::dmat4 const& modelViewMat) const ;
protected:
	std::vector<Abs_Entity*> gObjects;
};

