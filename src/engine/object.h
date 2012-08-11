/* 
 * File:   object.h
 * Author: lzuercher
 *
 * Created on 11 August 2012, 09:20
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include "Model_3DS.h"
#include "vector3.h"


class Object {
public:
  Object();
  Object(Model_3DS* meshcopy);
  void Draw();
  void copyMesh(Model_3DS &mesh);
  virtual ~Object();
  
  void loadMesh(char* filename);
  
  Vector3 pos;
  
protected:
  Model_3DS mesh;
  Model_3DS* model;

};

#endif	/* OBJECT_H */

