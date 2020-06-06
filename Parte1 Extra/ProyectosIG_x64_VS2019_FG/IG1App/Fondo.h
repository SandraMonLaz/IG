#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
class Fondo    // EXTRA 1
{
public:
	Fondo();
	void setSizeVP(double xw, double yh);
	void render();
	~Fondo();

private:
	Mesh* mMesh;
	Texture* textura;
	Texture* secondTexture;
	Camera* camera;

	Viewport* viewport;
};

