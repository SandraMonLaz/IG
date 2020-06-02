#pragma once
#include "Entity.h"
#include "IndexMesh.h"
#include "MbR.h"
class EntityWithIndexMesh :	public Abs_Entity
{
public:
	EntityWithIndexMesh(glm::dvec4 color) : Abs_Entity(),color(color) {
		
	}	
	~EntityWithIndexMesh() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	glm::dvec4 color;
};
//-------------------------------------------------------------------------
class Cubo : public EntityWithIndexMesh
{
public:
	Cubo(glm::dvec4 color) :EntityWithIndexMesh(color){
		mMesh = IndexMesh::generaIndexCuboConTapas(100);
		copper = false;
	}
	~Cubo() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void setCopper(bool b) { copper = b; }
	private:
	bool copper;
};
//-------------------------------------------------------------------------
class Cono : public EntityWithIndexMesh {
public:
	Cono(GLdouble h, GLdouble r, GLuint n, glm::dvec4 color) :EntityWithIndexMesh(color) {
		// h=altura del cono, r=radio de la base
		// n=número de muestras, m=número de puntos del perfil
		int m = 3;
		glm::dvec3* perfil = new glm::dvec3[m];
		perfil[0] = glm::dvec3(0.5, 0.0, 0.0);
		perfil[1] = glm::dvec3(r, 0.0, 0.0);
		perfil[2] = glm::dvec3(0.5, h, 0.0);
		mMesh = MbR::generaIndexMeshByRevolution(m, n, perfil);
	}
	~Cono() {};
};

