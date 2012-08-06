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

using namespace std;

class Object {
public:
  Object();
  Object(const char* filename);
  GLint loadObject(const char* filename);
  virtual ~Object();
  
  float* normals; // Stores the normals
  float* Faces_Triangles; // Stores the triangles
  float* vertexBuffer; // Stores the points which make the object
  long TotalConnectedPoints; // Stores the total number of connected verteces
  long TotalConnectedTriangles; // Stores the total number of connected triangles
private:
  GLint _texture;
  char _name[64];
};

#endif	/* OBJECT_H */

