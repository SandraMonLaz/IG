#include "Foto.h"
#include "IG1App.h"
void Foto::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//Color
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//Textura
		if (mTexture != nullptr)mTexture->bind(GL_REPEAT);
		mMesh->render();
		//Reseteamos los valores
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1.0);
		if (mTexture != nullptr)mTexture->unbind();
	}
}
void Foto::update() {
	mTexture->loadColorBuffer(IG1App::s_ig1app.getW(), IG1App::s_ig1app.getH());
}
