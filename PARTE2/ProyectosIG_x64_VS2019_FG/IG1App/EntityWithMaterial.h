#pragma once
#include "Entity.h"
#include "MbR.h"
#include "Material.h"
class EntityWithMaterial :	public Abs_Entity
{
public:
	EntityWithMaterial(glm::dvec4 color) : Abs_Entity(), color(color) , material(nullptr) {

	}
	~EntityWithMaterial() { if (material != nullptr) delete material; };
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void setMaterial(Material* m) { material = m; }
protected:
	glm::dvec4 color;
	Material* material;
};
class Esfera : public EntityWithMaterial {
public:
	Esfera(GLuint m, GLdouble r, GLuint p, glm::dvec4 color) :EntityWithMaterial(color) {
		int n = p + 2;
		glm::dvec3* vertices = new glm::dvec3[n + 2];
		for (int i = 0; i <= n; ++i) {
			GLdouble theta = i * 180 / (n);
			GLdouble c = cos(glm::radians(theta));
			GLdouble s = sin(glm::radians(theta));
			vertices[i] = glm::dvec3(r * s, -r * c, 0.0);
		}
		mMesh = MbR::generaIndexMeshByRevolution(n + 2, m, vertices);
	}
	~Esfera() {};
	void setGold() {
		material = new Material();
		material->setGold();
		color.r = 212 / 255.0; color.g = 175 / 255.0; color.b = 55 / 255.0;
	}
};

