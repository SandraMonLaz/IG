#include "MbR.h"

MbR* MbR::generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil)
{
	MbR* mesh = new MbR(nn, perfil, mm);
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = nn * mm;
	std::vector<glm::dvec3> vertices;
	vertices.reserve(mesh->mNumVertices);
	mesh->vVertices.reserve(mesh->mNumVertices);
	

	// Definir el número de vértices como nn*mm
	// Usar un vector auxiliar de vértices
	// dvec3* vertices = new dvec3[mesh->mNumVertices];
	for (int i = 0; i < nn; i++) {
		// Generar la muestra i-ésima de vértices
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(glm::radians(theta));
		GLdouble s = sin(glm::radians(theta));
		// R_y(theta) es la matriz de rotación alrededor del eje Y
		for (int j = 0; j < mm; j++) {
			int indice = i * mm + j;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			vertices.emplace_back(glm::dvec3(x, perfil[j].y, z));
		}
	}
	mesh->vVertices = vertices;

	//Calculamos los indices
	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn; i++) {
		// El contador j recorre los vértices del perfil,
		// de abajo arriba. Las caras cuadrangulares resultan
		// al unir la muestra i-ésima con la (i+1)%nn-ésima
		for (int j = 0; j < mm - 1; j++){
			// El contador indice sirve para llevar cuenta
			 // de los índices generados hasta ahora. Se recorre
			 // la cara desde la esquina inferior izquierda
			int indice = i * mm + j;
			mesh->vIndices.push_back(indice);
			mesh->vIndices.push_back((indice + mm) % (nn * mm));
			mesh->vIndices.push_back((indice + mm + 1) % (nn * mm));

			mesh->vIndices.push_back((indice + mm + 1) % (nn * mm));
			mesh->vIndices.push_back(indice + 1);
			mesh->vIndices.push_back(indice);
		}
	}
	mesh->buildNormalVector();
	

	return mesh;
}
