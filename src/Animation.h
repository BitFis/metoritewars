/* 
 * File:   Animation.h
 * Author: zurcherl
 *
 * Created on 8. August 2012, 16:11
 */

#ifndef ANIMATION_H
#define	ANIMATION_H

#include <vector>

#include "engine/vector3.h"
#include "engine/time-helper.h"

#include "engine/Model_3DS.h"

using namespace std;

class Animation {
public:
  
  //contains animations
  struct animationtype{
    Vector vertexpos; //targetposition
    timespec timepassed;
    timespec timestart;
  };
  
  Animation();
  virtual ~Animation();
  void addVertex(animationtype animationptr,Vector vertexpos, timespec timepassed, timespec timestart);
  
  vector<animationtype> animation;
  
private:
  
};

#endif	/* ANIMATION_H */

