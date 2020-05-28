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

class Cubo : public EntityWithIndexMesh
{
public:
	Cubo(glm::dvec4 color) :EntityWithIndexMesh(color){
		mMesh = IndexMesh::generaIndexCuboConTapas(100);
		copper = true;
	}
	~Cubo() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void setCopper(bool b) { copper = b; }
	private:
	bool copper;
};
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

class Esfera : public EntityWithIndexMesh {
public:
	Esfera(GLuint m,GLdouble r, GLuint p, glm::dvec4 color) :EntityWithIndexMesh(color) {
		// h=altura del cono, r=radio de la base
		// n=número de muestras, m=número de puntos del perfil

		/*glm::dvec3* perfil = new glm::dvec3[m + 2];
		double angle = 180 / m;
		for (int i = 0; i < m + 1 ; i++) {
			double x = cos(glm::radians(angle * i)) * r;
			double y = sin(glm::radians(angle * i)) * r;
			perfil[i] = glm::dvec3(y, -x, 0.0);
		}*/
		int n = p + 2;
		glm::dvec3* vertices = new glm::dvec3[n + 2];
		for (int i = 0; i <= n; ++i) {
			GLdouble theta = i * 180 / (n);
			GLdouble c = cos(glm::radians(theta));
			GLdouble s = sin(glm::radians(theta));
			vertices[i] = glm::dvec3(r * s, -r * c, 0.0);
		}

		this->mMesh = MbR::generaIndexMeshByRevolution(n + 2, m, vertices);

		//mMesh = MbR::generaIndexMeshByRevolution(m+4, n, perfil);
		gold = false;
	}
	~Esfera() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void setGold(bool b) { gold = b; }
private:
	bool gold;

};
