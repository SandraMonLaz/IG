#include "IndexMesh.h"

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
		/*if (vNormals.size() > 0) { // transfer normals
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}*/
		if (indices != nullptr) { // transfer vertices
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, indices);
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
	glDrawElements(mPrimitive, nNumIndices,	GL_UNSIGNED_INT, indices);
}

IndexMesh* IndexMesh::generaIndexCuboConTapas(GLdouble l)
{
	unsigned int stripIndices[] =
	{ 0, 1, 2, 2, 1, 3, 2, 3, 4, 4, 3,5,4,5,6,6,5,7,6,7,0,0,7,1,4,6,2,2,6,0,1,7,3,3,7,5 };
	IndexMesh* mesh = new IndexMesh(stripIndices);

	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vIndices.reserve(36);

	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2); //v0
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2); //v1
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2); // v2
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);  //v3
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);  //v4
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2); //v5
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);  //v6
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);  // v7

	mesh->vNormals.emplace_back(1, 1, -1);
	mesh->vNormals.emplace_back(1, -1, -1);
	mesh->vNormals.emplace_back(1, 1, 1);
	mesh->vNormals.emplace_back(1, -1, 1);
	mesh->vNormals.emplace_back(-1, 1, 1);
	mesh->vNormals.emplace_back(-1, -1, 1);
	mesh->vNormals.emplace_back(-1, 1, -1);
	mesh->vNormals.emplace_back(-1, -1, -1);

	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);

	return nullptr;
}
