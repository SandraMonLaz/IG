#include "Cristalera.h"
using namespace glm;
void Cristalera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		//Color
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//Texture
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		mMesh->render();
		//Reset
		if (mTexture != nullptr) mTexture->unbind();

	}
}
