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
	Esfera(GLuint p, GLdouble r, GLuint m, glm::dvec4 color) :EntityWithMaterial(color) {
		glm::dvec3* vertices = new glm::dvec3[p];
		double radX = 0, radY = 3 * glm::pi<double>() / 2;

		for (int i = 0; i < p; ++i) {
			vertices[i]=(glm::dvec3(0.5 + r * sin(radX), r * sin(radY), 0.0));
			radX += glm::pi<double>() / (p - 1);
			radY += glm::pi<double>() / (p - 1);
		}
		mMesh = MbR::generaIndexMeshByRevolution(m, p, vertices);
	}
	~Esfera() {};
	void setGold() {
		material = new Material();
		material->setGold();
		color.r = 212 / 255.0; color.g = 175 / 255.0; color.b = 55 / 255.0;
	}
};

