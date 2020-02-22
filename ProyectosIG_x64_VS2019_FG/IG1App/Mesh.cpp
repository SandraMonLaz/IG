#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }
    if (vTexCoords.size() > 0) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   
  }
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
    Mesh* mesh = generaRectangulo(w,h);
    mesh->vTexCoords.reserve(4);
    mesh->vTexCoords.emplace_back(0, rh);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(rw, rh);
    mesh->vTexCoords.emplace_back(rw, 0);
    return mesh;
}
Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_FAN;
    mesh->mNumVertices = (2 * np) + 2;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vTexCoords.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
    mesh->vTexCoords.emplace_back(0.5, 0.5);
    double angle = 90;
    double radio = re;
    double rText = 0.5;
    bool exterior = true;
    for (int i = 0; i < ((np * 2) + 1); ++i) {
        if (exterior) {
            radio = re;
            exterior = false;
            rText = 0.5;
        }
        else {
            radio = re / 2;
            exterior = true;
            rText = 0.25;
        }
        double x = radio * cos(radians(angle));
        double y = radio * sin(radians(angle));
        mesh->vVertices.emplace_back(x, y, h);
        mesh->vTexCoords.emplace_back(0.5 + rText * cos(radians(angle)), 0.5 + rText * sin(radians(angle)));

        angle += 360.0 / ((np * 2));
    }

    return mesh;
}
Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_FAN;
    mesh->mNumVertices = (2*np)+ 2;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
    double angle = 90;
    double radio = re;
    bool exterior = true;
    for (int i = 0; i < ((np* 2) + 1); ++i) {
        if (exterior) {
            radio = re;
            exterior = false;
        }
        else {
            radio = re / 2;
            exterior = true;
        }
        double x = radio * cos(radians(angle));
        double y = radio * sin(radians(angle));
        mesh->vVertices.emplace_back(x, y, h);

        angle += 360.0 / ((np*2));
    }
    
    return mesh;
}

Mesh* Mesh::generaCajaTexCor(GLdouble nl) {
    Mesh* mesh = Mesh::generaContCubo(nl);
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    

    mesh->vTexCoords.emplace_back(0,1);//V0
    mesh->vTexCoords.emplace_back(0, 0);//V1
    mesh->vTexCoords.emplace_back(1, 1);//V2
    mesh->vTexCoords.emplace_back(1, 0);//V3
    mesh->vTexCoords.emplace_back(2, 1);//V4
    mesh->vTexCoords.emplace_back(2, 0);//V5
    mesh->vTexCoords.emplace_back(3, 1);//V6
    mesh->vTexCoords.emplace_back(3, 0);//V7
    mesh->vTexCoords.emplace_back(4, 1);//V8
    mesh->vTexCoords.emplace_back(4, 0);//V9


    return mesh;
}

Mesh* Mesh:: generaContCubo(GLdouble ld) {
    Mesh* mesh = new Mesh();
    
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(-ld / 2, ld / 2, ld / 2); //v0
    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2); //v1
    mesh->vVertices.emplace_back(ld / 2, ld / 2, ld / 2); // v2

    mesh->vVertices.emplace_back(ld / 2, -ld / 2, ld / 2);  //v3
    mesh->vVertices.emplace_back(ld / 2, ld / 2, -ld / 2);  //v4
    mesh->vVertices.emplace_back(ld / 2, -ld / 2, -ld / 2); //v5
    mesh->vVertices.emplace_back(-ld / 2, ld / 2, -ld / 2);  //v6

    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, -ld / 2);  // v7
    mesh->vVertices.emplace_back(-ld / 2, ld / 2, ld / 2); //v0
    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2); //v1


    return mesh;
}
Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
    Mesh* mesh = generaRectangulo(w, h);
    mesh->vColors.reserve(4);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    return mesh;
}
Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(4);

    glm::dvec3 v0, v1, v2, v3;
    v0.x = - w / 2; v0.y =   h / 2;     
    v1.x = - w / 2; v1.y = - h / 2;   
    v2.x =  w / 2; v2.y =  h / 2; 
    v3.x = w / 2; v3.y = -h / 2;

    mesh->vVertices.emplace_back(v0.x, v0.y, 0.0);
    mesh->vVertices.emplace_back(v1.x, v1.y, 0.0);
    mesh->vVertices.emplace_back(v2.x, v2.y, 0.0);
    mesh->vVertices.emplace_back(v3.x, v3.y, 0.0);

    return mesh;
}
Mesh* Mesh::generaTrianguloRGB(GLdouble rd) {
    Mesh* mesh = generaPoligono(3, rd);
    mesh->mPrimitive = GL_TRIANGLES;
    // añade el vector de colores
    mesh->vColors.reserve(3);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    
    return mesh;
}
 Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
     Mesh* triangulo = generaPoligono(3, rd);
     Mesh* mesh = new Mesh();

     mesh->mPrimitive = GL_POINTS;
     mesh->mNumVertices = numP;
     mesh->vVertices.reserve(mesh->mNumVertices);

     glm::dvec3 pMiddle, rnd, last;
     pMiddle.x = (triangulo->vVertices[0].x + triangulo->vVertices[1].x) / 2;
     pMiddle.y = (triangulo->vVertices[0].y + triangulo->vVertices[1].y) / 2;
     pMiddle.z = (triangulo->vVertices[0].z + triangulo->vVertices[1].z) / 2;
     mesh->vVertices.emplace_back(pMiddle.x, pMiddle.y, pMiddle.z);


     while (numP > 0) {
         last = pMiddle;
         rnd = triangulo->vVertices[rand() % 3];
         pMiddle.x = (last.x + rnd.x) / 2;
         pMiddle.y = (last.y + rnd.y) / 2;
         pMiddle.z = (last.z + rnd.z) / 2;
         mesh->vVertices.emplace_back(pMiddle.x, pMiddle.y, pMiddle.z);
         numP-- ;
     }

     delete triangulo; triangulo = nullptr;
     return mesh;
 }
Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd){
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_LINE_LOOP;
    mesh->mNumVertices = numL;
    mesh->vVertices.reserve(mesh->mNumVertices);

    double angle = 90;
    for (int i = 0; i < numL; ++i) {
        double x = rd * cos(radians(angle));
        double y = rd * sin(radians(angle));
        mesh->vVertices.emplace_back(x, y, 0.0);
        //mesh->vColors.emplace_back(1.0, 1.0, 0.0, 1.0);
        angle += 360.0 / numL;
    }
    return mesh;
}
Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

