#pragma once
#include "Entity.h"
#include "IndexMesh.h"
class EntityWithIndexMesh :	public Abs_Entity
{
public:
	EntityWithIndexMesh() : Abs_Entity() {
		mMesh = IndexMesh::generaIndexCuboConTapas(100);
	}	
	~EntityWithIndexMesh() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

