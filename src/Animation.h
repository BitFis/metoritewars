/* 
 * File:   Animation.h
 * Author: zurcherl
 *
 * Created on 8. August 2012, 16:11
 */

#ifndef ANIMATION_H
#define	ANIMATION_H

#include "utility/vector3.h"
#include "engine/time-helper.h"

#include "engine/Model_3DS.h"

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
  animationtype* addVertex();
  
  animationtype* animation;
  
private:
  
};

#endif	/* ANIMATION_H */

