#pragma once
#include "IndexMesh.h"
class MbR :	public IndexMesh
{
public:
	MbR(int n, glm::dvec3* perfil, int m) : IndexMesh(), n(n), perfil(perfil), m(m) {}
	~MbR() { delete[] perfil; }
	static MbR* generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil, glm::dvec4 color);

private:
	int n; //nº de muestras
	glm::dvec3* perfil; //array de vertices
	int m; //nº de puntos del perfil
};

