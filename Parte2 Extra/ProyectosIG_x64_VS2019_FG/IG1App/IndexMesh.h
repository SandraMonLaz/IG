#pragma once
#include "Mesh.h"
class IndexMesh : public Mesh
{
protected:
	std::vector<GLuint> vIndices;    // color array
	GLuint nNumIndices = 36;
public:
	IndexMesh() : Mesh() {}
	IndexMesh(std::vector<GLuint> v) : Mesh() { mPrimitive = GL_TRIANGLES; vIndices = v; }
	~IndexMesh() {}
	virtual void render() const;
	virtual void draw() const;
	static IndexMesh* generaAnilloCuadrado();
	static IndexMesh* generateGrid(GLdouble lado, GLuint nDiv);
	static IndexMesh* generateGridTex(GLdouble lado, GLuint nDiv);

	void buildNormalVector();

	static IndexMesh* generaIndexCuboConTapas(GLdouble l);
};

