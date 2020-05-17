#pragma once
#include "Entity.h"
#include "IndexMesh.h"
#include "MbR.h"
class EntityWithIndexMesh :	public Abs_Entity
{
public:
	EntityWithIndexMesh() : Abs_Entity() {
		
	}	
	~EntityWithIndexMesh() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	
};

class Cubo : public EntityWithIndexMesh
{
public:
	Cubo(glm::dvec4 color) :EntityWithIndexMesh(){
		mMesh = IndexMesh::generaIndexCuboConTapas(100,color);
	}
	~Cubo() {};
};
class Cono : public EntityWithIndexMesh {
public:
	Cono(GLdouble h, GLdouble r, GLuint n, glm::dvec4 color) :EntityWithIndexMesh() {
		// h=altura del cono, r=radio de la base
		// n=número de muestras, m=número de puntos del perfil
		int m = 3;
		glm::dvec3* perfil = new glm::dvec3[m];
		perfil[0] = glm::dvec3(0.5, 0.0, 0.0);
		perfil[1] = glm::dvec3(r, 0.0, 0.0);
		perfil[2] = glm::dvec3(0.5, h, 0.0);
		mMesh = MbR::generaIndexMeshByRevolution(m, n, perfil, color);
	}
	~Cono() {};
};

class Esfera : public EntityWithIndexMesh {
public:
	Esfera(GLuint m,GLdouble r, GLuint n, glm::dvec4 color) :EntityWithIndexMesh() {
		// h=altura del cono, r=radio de la base
		// n=número de muestras, m=número de puntos del perfil
		glm::dvec3* perfil = new glm::dvec3[m + 2];
		double angle = 180 / m;
		for (int i = 0; i < m + 1 ; i++) {
			double x = cos(glm::radians(angle * i)) * r;
			double y = sin(glm::radians(angle * i)) * r;
			perfil[i] = glm::dvec3(y, -x, 0.0);
		}
		mMesh = MbR::generaIndexMeshByRevolution(m + 2, n, perfil, color);
	}
	~Esfera() {};
};
