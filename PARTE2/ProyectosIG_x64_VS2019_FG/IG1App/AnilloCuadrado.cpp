#include "AnilloCuadrado.h"

AnilloCuadrado::AnilloCuadrado() :Abs_Entity()
{
	mMesh = Mesh::generaAnilloCuadrado();
}

void AnilloCuadrado::draw() const
{
	unsigned int stripIndices[] =
	{ 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, stripIndices);

}

void AnilloCuadrado::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mMesh->render();
	}
}
