#include "IndexMesh.h"
#include <ext\quaternion_geometric.hpp>
using namespace glm;

void IndexMesh::render() const
{

	if (vVertices.size() > 0) {  // transfer data

	// transfer the coordinates of the vertices

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}
		if (vTexCoords.size() > 0) { // transfer Texture
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}
		if (vNormals.size() > 0) { // transfer normals
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
		if (vIndices.size() > 0) { // transfer vertices
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices.data());
		}
		draw();
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);

	}
}
void IndexMesh::draw() const {
	if (vIndices.size() > 0) {
		glDrawElements(mPrimitive, vIndices.size(), GL_UNSIGNED_INT, vIndices.data());
	}
}

IndexMesh* IndexMesh::generaIndexCuboConTapas(GLdouble ld)
{

	std::vector<GLuint> stripIndices({
		0,1,2, 2,1,3,
		2,3,4, 4,3,5,
		4,5,6, 6,5,7,
		6,7,0, 0,7,1,
		4,6,2, 2,6,0,
		1,7,3, 3,7,5 });

	IndexMesh* mesh = new IndexMesh(stripIndices);

	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vIndices.reserve(36);

	//vertices caja Parte1
	mesh->vVertices.emplace_back(-ld / 2, ld / 2, ld / 2); //v0
	mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2); //v1
	mesh->vVertices.emplace_back(ld / 2, ld / 2, ld / 2); // v2
	mesh->vVertices.emplace_back(ld / 2, -ld / 2, ld / 2);  //v3
	mesh->vVertices.emplace_back(ld / 2, ld / 2, -ld / 2);  //v4
	mesh->vVertices.emplace_back(ld / 2, -ld / 2, -ld / 2); //v5
	mesh->vVertices.emplace_back(-ld / 2, ld / 2, -ld / 2);  //v6
	mesh->vVertices.emplace_back(-ld / 2, -ld / 2, -ld / 2);  // v7


	mesh->buildNormalVector();


	return mesh;
}



IndexMesh* IndexMesh::generaAnilloCuadrado() {
	std::vector<GLuint> v({ 0,1,2,3,4,5,6,7,0,1 });
	IndexMesh* mesh = new IndexMesh(v);
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(8);
	mesh->vColors.reserve(8);
	mesh->vIndices.reserve(10);
	//---------------------VERTICES---------------------------
	mesh->vVertices.emplace_back(glm::dvec3(30.0, 30.0, 0.0));
	mesh->vVertices.emplace_back(glm::dvec3(10.0, 10.0, 0.0));
	mesh->vVertices.emplace_back(glm::dvec3(70.0, 30.0, 0.0));
	mesh->vVertices.emplace_back(glm::dvec3(90.0, 10.0, 0.0));
	mesh->vVertices.emplace_back(glm::dvec3(70.0, 70.0, 0.0));
	mesh->vVertices.emplace_back(glm::dvec3(90.0, 90.0, 0.0));
	mesh->vVertices.emplace_back(glm::dvec3(30.0, 70.0, 0.0));
	mesh->vVertices.emplace_back(glm::dvec3(10.0, 90.0, 0.0));
	//---------------------COLORES---------------------------
	mesh->vColors.emplace_back(glm::dvec4(0.0, 0.0, 0.0, 1.0));
	mesh->vColors.emplace_back(glm::dvec4(1.0, 0.0, 0.0, 1.0));
	mesh->vColors.emplace_back(glm::dvec4(0.0, 1.0, 0.0, 1.0));
	mesh->vColors.emplace_back(glm::dvec4(0.0, 0.0, 0.0, 1.0));
	mesh->vColors.emplace_back(glm::dvec4(1.0, 1.0, 0.0, 1.0));
	mesh->vColors.emplace_back(glm::dvec4(1.0, 0.0, 1.0, 1.0));
	mesh->vColors.emplace_back(glm::dvec4(0.0, 1.0, 1.0, 1.0));
	mesh->vColors.emplace_back(glm::dvec4(1.0, 0.0, 0.0, 1.0));

	return mesh;
}

IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint nDiv)
{
	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;
	double distancia = lado / nDiv;
	double posX = -(lado / 2);
	double posZ = -(lado / 2);
	mesh->vVertices.reserve((nDiv+1)*(nDiv+1));
	//Bucle de las filas
	for (int i = 0; i < nDiv + 1; i++) {
		//Bucle de las columnas
		for (int j = 0; j < nDiv+1; j++) {
			mesh->vVertices.emplace_back(glm::dvec3(posX, 0, posZ));
			posX += distancia;
		}
		posZ += distancia;
		posX = -(lado/2);
	}

	int nn =nDiv+1;
	int mm = nDiv+1;
	mesh->nNumIndices = 6*nDiv*nDiv;	
	mesh->vIndices.reserve(mesh->nNumIndices);
	//Calculamos los indices
	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nDiv; i++) {
		// El contador j recorre los vértices del perfil,
		// de abajo arriba. Las caras cuadrangulares resultan
		// al unir la muestra i-ésima con la (i+1)%nn-ésima
		for (int j = 0; j < nDiv; j++) {
			// El contador indice sirve para llevar cuenta
			 // de los índices generados hasta ahora. Se recorre
			 // la cara desde la esquina inferior izquierda
			int indice = i * mm + j;
			mesh->vIndices.emplace_back(indice);
			mesh->vIndices.emplace_back((indice + mm) % (nn * mm));
			mesh->vIndices.emplace_back((indice + mm + 1) % (nn * mm));

			mesh->vIndices.emplace_back((indice + mm + 1) % (nn * mm));
			mesh->vIndices.emplace_back(indice + 1);
			mesh->vIndices.emplace_back(indice);
		}
	}
	mesh->buildNormalVector();
	return mesh;
}

IndexMesh* IndexMesh::generateGridTex(GLdouble lado, GLuint nDiv)
{
	IndexMesh* mesh = generateGrid(lado,nDiv);
	GLdouble distancia = 1 / GLdouble(nDiv);

	//Ponemos las mismas coordenadas que en los vertices solo que en el rango [0,1]
	double posX = 0;
	double posY = 0;
	mesh->vTexCoords.reserve(mesh->vVertices.size());
	for (int i = 0; i < nDiv + 1; i++) {
		for (int j = 0; j < nDiv + 1; j++) {
			mesh->vTexCoords.emplace_back(glm::dvec2(posX, posY));
			posX += distancia;
		}
		posY += distancia;
		posX = 0;
	}
	return mesh;
}


void IndexMesh::buildNormalVector() {
	for (int q = 0; q < vVertices.size(); q++) {
		vNormals.emplace_back(glm::dvec3(0, 0, 0));
	}
	//n = normalize(cross((v2 - v1), (v0 - v1)))
	for (int i = 0; i < vIndices.size() / 3; i++) {
		glm::dvec3 a = vVertices.at(vIndices.at(i * 3));
		glm::dvec3 b = vVertices.at(vIndices.at(i * 3 + 1));
		glm::dvec3 c = vVertices.at(vIndices.at(i * 3 + 2));
		glm::dvec3 normal = normalize(cross(b - a, c - a));

		vNormals[vIndices.at(i * 3 + 2)] += normal;
		vNormals[vIndices.at(i * 3 + 1)] += normal;
		vNormals[vIndices.at(i * 3 + 0)] += normal;
	}
	for (int p = 0; p < vNormals.size(); p++) {
		vNormals.at(p) = normalize(vNormals.at(p));
	}
}


