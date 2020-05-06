#pragma once
#include "Mesh.h"
class IndexMesh : public Mesh
{
protected:
	GLuint* indices = nullptr; // tabla de índices
	GLuint nNumIndices = 0;
public:
	IndexMesh(GLuint* i): Mesh() { mPrimitive = GL_TRIANGLES; indices = i; }
	~IndexMesh() { delete indices; }
	virtual void render() const;
	virtual void draw() const;

	static IndexMesh* generaIndexCuboConTapas(GLdouble l);
};

