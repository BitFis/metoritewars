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

#define OBJECT_MAX_POINTS_PER_VERTEX 4
#define OBJECT_TOTAL_FLOATS_IN_TRIANGLE 9
#define OBJECT_TOTAL_FLOATS_IN_RECTANGLE 12

using namespace std;

class Object {
public:
  Object();
  Object(const char* filename);
  GLint loadObject(const char* filename);
  float* calculateNormal( float *coord1, float *coord2, float *coord3 );
  virtual ~Object();
  
  float* normals; // Stores the normals
  float* Faces_Triangles; // Stores the triangles
  float* vertexBuffer; // Stores the points which make the object
  long TotalConnectedPoints; // Stores the total number of connected verteces
  long TotalConnectedTriangles; // Stores the total number of connected triangles
private:
  GLint _texture;
  string _name;
  string _materialfile;
};

#endif	/* OBJECT_H */

