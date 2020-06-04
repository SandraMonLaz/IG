#include "EntityWithIndexMesh.h"
#include <gtc\type_ptr.hpp>

void EntityWithIndexMesh::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glColor3f(color.x, color.y, color.z);
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mMesh->render();
	}
}

/*void Esfera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
	
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		if (!gold)
			glColor4dv(value_ptr(color));
		else {
			glm::dvec4 col;
			col.x = 212 / 255.0; col.y = 175 / 255.0; col.z = 55 / 255.0;
			glColor4dv(value_ptr(col));

		}
		glm::fvec4 ambient = { 0.24725f,0.1995f,0.0475f,1.0f };
		glm::fvec4 difuse = { 0.75164f,0.60648f,0.22648f,1.0f };
		glm::fvec4 specular = { 0.628281f,0.555802f,0.366065f,1.0f };

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(difuse));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular));

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 51.2);
		mMesh->render();
		glColor3f(1, 1, 1);

	}
}*/

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		if (!copper)
			glColor4dv(value_ptr(color));
		else {
			glm::dvec4 col;
			col.x = 184 / 255.0; col.y = 115 / 255.0; col.z = 51 / 255.0;
			glColor4dv(value_ptr(col));

		}
		glm::fvec4 ambient = { 0.19125f,0.0735f,0.0225f,1.0f };
		glm::fvec4 difuse = { 0.7038f,0.27048f,0.0828f,1.0f };
		glm::fvec4 specular = { 0.256777f,0.137622f,0.086014f,1.0f };

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(difuse));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular));

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 12.8);
		mMesh->render();
		glColor3f(1, 1, 1);

	}
}

void Grid::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3f(1, 0, 0);

		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		upload(aMat);
		mMesh->render();
		glColor3f(1, 1, 1);
		if (mTexture != nullptr) mTexture->unbind();
		//glDisable(GL_COLOR_MATERIAL);

	}
}
