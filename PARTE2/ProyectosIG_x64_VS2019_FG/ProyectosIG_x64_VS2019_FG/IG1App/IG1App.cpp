#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------


IG1App::IG1App()
{
	mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
	animacionActivada = false;
	dobleVentana = false;
}


void IG1App::close()
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;
	fondo = new Fondo();

	mCamera->set2D();
	mScene->init();
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL()
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   

	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);
	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free()
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
	delete fondo; fondo = nullptr;
}

//-------------------------------------------------------------------------

void IG1App::display() const
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer
	fondo->render();
	if (dobleVentana) {
		display2Vistas();
	}
	else {
		mViewPort->setSize(mWinW, mWinH);
		mViewPort->setPos(0, 0);
		mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	}
	glutSwapBuffers();	// swaps the front and back buffer
}

void IG1App::display2Vistas() const {
	Camera auxCam = *mCamera;
	Viewport auxVP = *mViewPort;

	mViewPort->setSize(mWinW / 2, mWinH );
	auxCam.setSize(mViewPort->width(),mViewPort->height());
	mViewPort->setPos(0, 0);
	mScene->render(auxCam);  // uploads the viewport and camera to the GPU

	mViewPort->setPos(mWinW / 2, 0);
	auxCam.setCenital();
	mScene->render(auxCam);

	*mViewPort = auxVP;
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
		mScene->update();
		break;
	case 'U':
		if (!animacionActivada)
			animacionActivada = true;
		else
			animacionActivada = false;
		break;
	case 'F':
		mScene->saveBMP(mScene->fotoT);
		break;
	case 'p':
		mCamera->changePrj();
		break;
	case 'k':
		dobleVentana = !dobleVentana;
		break;
	case 'q':
		mScene->setLight(true, 0);
		break;
	case 'w':
		mScene->setLight(false, 0);
		break;
	case 'a':
		mScene->setLight(true, 1);
		break;
	case 's':
		mScene->setLight(false, 1);
		break;
	case 'z':
		mScene->setLight(true, 2);
		break;
	case 'x':
		mScene->setLight(false, 2);
		break;
	case 't':
		mScene->setLight(true, 3);
		break;
	case 'g':
		mScene->setLight(false, 3);
		break;
	case 'd':
		mScene->setLight(true, 4);
		break;
	case 'f':
		mScene->setLight(false, 4);
		break;
	case 'e':
		mScene->ApagarEscena();
		break;
	case 'y':
		mScene->move();
		break;
	case '0':
		mScene->setState(0);
		mCamera->set2D();
		break;
	case '1':
		mScene->setState(1);
		mCamera->set3D();
		break;
	case '2':
		mScene->setState(2);
		mCamera->set3D();
		break;
	case '3':
		mScene->setState(3);
		mCamera->set3D();
		break;
	case '4':
		mScene->setState(4);
		mCamera->set3D();
		break;
	case '5':
		mScene->setState(5);
		mCamera->set3D();
		break;
	case '6':
		mScene->setState(6);
		mCamera->set3D();
		break;
	case '7':
		mScene->setState(7);
		mCamera->set3D();
		break;
	case '8':
		mScene->setState(8);
		mCamera->set3D();
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->moveLR(-2);   // rotates -1 on the X axis
		else
			mCamera->moveLR(2);    // rotates 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->moveLR(2);      // rotates 1 on the Y axis 
		else
			mCamera->moveLR(-2);     // rotate -1 on the Y axis 
		break;
	case GLUT_KEY_UP:
		mCamera->moveUD(2);    // rotates 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		mCamera->moveUD(-2);   // rotates -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------


void IG1App::update() {

	if (glutGet(GLUT_ELAPSED_TIME) - mLastUpdateTime > 20 && animacionActivada) {
		mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
		mScene->update();
		glutPostRedisplay();
	}
}

void IG1App::mouse(int button, int state, int x, int y) {
	mMouseButt = button;
	// (x, y) es la posición del ratón en la ventana,
	// siendo (0,0) la esquina (left, top)
	// Guardamos las coordenadas del mouse en un atributo de la aplicación
	mMouseCoord = glm::dvec2(x, mWinH - y);
}



void IG1App::motion(int x, int y) {
	// guardamos la anterior posición en var. temp.
	glm::dvec2 mp = mMouseCoord;
	// Guardamos la posición actual
	mMouseCoord = glm::dvec2(x, mWinH - y);
	mp = (mp - mMouseCoord); // calculamos el desplazamiento realizado
	if (mMouseButt == GLUT_LEFT_BUTTON) {
		mCamera->orbit(mp.x * 0.05, mp.y); // sensitivity = 0.05
	}
	else if (mMouseButt == GLUT_RIGHT_BUTTON) {
		mCamera->moveLR(mp.x);
		mCamera->moveUD(mp.y);
	}
	glutPostRedisplay();
}

void IG1App::mouseWheel(int n, int d, int x, int y) {
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)
	if (mdf == GLUT_ACTIVE_CTRL) {
		mCamera->setScale(+0.01 * d);
	}
	// d es la dirección de la rueda (+1 / -1)
	else {
		if (d == 1) mCamera->moveFB(5);
		else mCamera->moveFB(-5);
	}
	glutPostRedisplay();
}
