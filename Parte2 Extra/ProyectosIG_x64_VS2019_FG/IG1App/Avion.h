#pragma once
#include "CompoundEntity.h"
#include "Light.h"
class Avion :	public CompoundEntity
{
public:
	Avion(int r, SpotLight* faro);
	~Avion() {};
	void render(glm::dmat4 const& modelViewMat) const;

	void move();
private:
	CompoundEntity* helicesAvion;
	int radioOrbita;
	double angle;
	double heliceAngle;
	SpotLight* luzFoco;
};

