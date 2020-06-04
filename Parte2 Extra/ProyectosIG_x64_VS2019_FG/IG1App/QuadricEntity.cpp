#include "QuadricEntity.h"



void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aqu� se puede fijar el color de la esfera as�:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.r, color.g, color.b);
	// Aqu� se puede fijar el modo de dibujar la esfera:
	//gluQuadricDrawStyle(q, GLU_LINE);
	gluSphere(q, r, 50, 50);
	// Aqu� se debe recuperar el color:
	// glColor3f(1.0, 1.0, 1.0);
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aqu� se puede fijar el color de la esfera as�:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.r, color.g, color.b);
	// Aqu� se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluCylinder(q, base, topRadius, h, 10, 10);
	// Aqu� se debe recuperar el color:
	// glColor3f(1.0, 1.0, 1.0);
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aqu� se puede fijar el color de la esfera as�:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.r, color.g, color.b);
	// Aqu� se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluPartialDisk(q, innerRadius, outerRadius, 10, rings, startAngle, sweepAngle);
	// Aqu� se debe recuperar el color:
	// glColor3f(1.0, 1.0, 1.0);
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aqu� se puede fijar el color de la esfera as�:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.r, color.g, color.b);
	// Aqu� se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluDisk(q, innerRadius, outerRadius, 10, rings);
	// Aqu� se debe recuperar el color:
	// glColor3f(1.0, 1.0, 1.0);
}
