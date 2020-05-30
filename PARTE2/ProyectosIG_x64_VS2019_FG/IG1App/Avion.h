#pragma once
#include "CompoundEntity.h"
class Avion :	public CompoundEntity
{
public:
	Avion();
	~Avion() {};

	void move();
private:
	CompoundEntity* helicesAvion;
	double angle;
	double heliceAngle;
};

