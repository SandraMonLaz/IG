#pragma once
#include "Light.h"
#include "CompoundEntity.h"
#include "GridCube.h"
#include "Texture.h"
#include "EntityWithIndexMesh.h"

using namespace glm;
class SirenCube :
	public CompoundEntity
{

public:
	SirenCube(Texture* arriba, Texture* lateral, int r, SpotLight* sp);
	~SirenCube() {}
	void move();
	void render(glm::dmat4 const& modelViewMat) const;


private:
	int radioOrbita;
	double angle;
	SpotLight* siren;
	dmat4 matrizLuz;
};

