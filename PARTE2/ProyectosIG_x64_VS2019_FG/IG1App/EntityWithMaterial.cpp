#include "EntityWithMaterial.h"

void EntityWithMaterial::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3f(color.r, color.g, color.b);
		if (material != nullptr) material->upload();
		mMesh->render();
		glColor3f(1, 1, 1);
	}
}
