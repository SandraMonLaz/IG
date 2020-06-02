#pragma once
#include "Entity.h"
class QuadricEntity : public Abs_Entity
{
public:
	QuadricEntity() {
		q = gluNewQuadric();
	}
	~QuadricEntity() { gluDeleteQuadric(q); };

	void setColor(glm::fvec3 c) { color = c; }
protected:
	GLUquadricObj* q;
	glm::fvec3 color;
};

//-----------------------------------------------
class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r) : QuadricEntity(), r(r) {} // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};
//-------------------------------------------------
class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble base, GLdouble topRadius, GLdouble h) : QuadricEntity(), base(base), topRadius(topRadius), h(h) {};
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble base, topRadius, h;
};
//-------------------------------------------------
class Disk : public QuadricEntity {
public:
	Disk(GLdouble innerRadius, GLdouble outerRadius, GLdouble rings) :
		QuadricEntity(), innerRadius(innerRadius), outerRadius(outerRadius), rings(rings) {};
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius, outerRadius, rings;
};
//-------------------------------------------------
class PartialDisk : public QuadricEntity {
public:
	PartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle, GLdouble rings) :
		QuadricEntity(), innerRadius(innerRadius), outerRadius(outerRadius), startAngle(startAngle), sweepAngle(sweepAngle), rings(rings) {}
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius, outerRadius, startAngle, sweepAngle, rings;
};

