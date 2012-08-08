/* 
 * File:   Object.h
 * Author: lzuercher
 *
 * Created on 06 August 2012, 19:53
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <iostream> //get helpful function and classes
#include <GL/freeglut.h>
#include <fstream>
#include <string>
#include <math.h>
#include <GL/glext.h>

#include "GLTexture.h"

#define OBJECT_MAX_POINTS_PER_VERTEX 4
#define OBJECT_TOTAL_FLOATS_IN_TRIANGLE 9
#define OBJECT_TOTAL_FLOATS_IN_RECTANGLE 12

using namespace std;

class Object {
public:
  Object();
  Object(const char* filename);
  int loadObject(const char* filename);
  int calculateNormal( float *coord1, float *coord2, float *coord3, float* norm  );
  GLint loadBmpTexture(char* filename);
  void Draw();
  virtual ~Object();
  
  float* normals; // Stores the normals
  float* Faces_Triangles; // Stores the triangles
  float* vertexBuffer; // Stores the points which make the object
  float* textureBuffer; // Stores the texturecoordinates
  long TotalConnectedPoints; // Stores the total number of connected verteces
  long TotalConnectedTriangles; // Stores the total number of connected triangles
private:
  GLint  _texture;
  string _name;
  string _materialfile;
	int width;										// Texture's width
	int height;										// Texture's height
};

#endif	/* OBJECT_H */

