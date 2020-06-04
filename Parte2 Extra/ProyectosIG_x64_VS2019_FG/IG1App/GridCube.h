#pragma once
#include "CompoundEntity.h"
#include "EntityWithIndexMesh.h"
#include "Texture.h"
class GridCube :
	public CompoundEntity
{
public:
	GridCube(Texture* arriba,Texture* lateral);
	~GridCube() {}

private:
};

