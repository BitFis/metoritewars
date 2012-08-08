/* 
 * File:   Object.h
 * Author: lzuercher
 *
 * Created on 06 August 2012, 19:53
 */

#ifndef OBJECT_H
#define	OBJECT_H

<<<<<<< HEAD:src/Object.h
#include "utility/Model_3DS.h"
=======
#include <iostream> //get helpful function and classes
#include <GL/freeglut.h>
#include <fstream>
#include <string>
#include <math.h>
#include <GL/glext.h>

#include "GLTexture.h"
>>>>>>> 60e1f97db0d97ee60e84c42128db1004799b9c74:src/engine/Object.h

#define OBJECT_MAX_POINTS_PER_VERTEX 4
#define OBJECT_TOTAL_FLOATS_IN_TRIANGLE 9
#define OBJECT_TOTAL_FLOATS_IN_RECTANGLE 12

using namespace std;

class Object {
public:
  Object();
  ~Object();
  
private:
  
  
};

#endif	/* OBJECT_H */

