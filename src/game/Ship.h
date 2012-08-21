/* 
 * File:   Ship.h
 * Author: zurcherl
 *
 * Created on 16. August 2012, 10:55
 */

#ifndef SHIP_H
#define	SHIP_H

#include <irrlicht/irrlicht.h>
#include "Shot.h"
#include "../engine/Angle.h"
#include <cmath>

#include <iostream>

using namespace irr;
using namespace std;

class Ship {
public:
  Ship(const char* filename, scene::ISceneManager* smgr);
  float move(int move, float deltaTime, float* speed);
  void rotate(int rotate, float deltaTime);
  void moveFor(float deltaTime);
  void stop();
  void moveBack(float deltaTime);
  void update(float DeltaTime);
  
  void shoot(float passedTime);
  
  Shot* getShots();
  
  core::vector3df getPosVec3df();
  scene::ISceneNode* getShipNode();
  
  virtual ~Ship();
private:
  
  void autoSlowdown(float* speed, float movspeed, bool* backMovement, bool* forMovement, float DeltaTime);
  
  Shot* shots;
  
  scene::ISceneManager* smgr;
  scene::IAnimatedMeshSceneNode* ship;
  
  float DeltaTime;
  
  float maxSpeed; //max possible speed
  float maxRot; //max rotation
  
  float lastshot; //to set shot timeout
  
  core::vector3df speed; //current move speed
  float acceleration;
  
  float rotaccel;
  float rotspeed; //rotation boost
  Angle rotation; //current rotation
  
  bool movefor; //moving forward
  bool moveback; //moving backwards
  
  bool rotright; //right rotation
  bool rotleft; //left rotation
  
  float timeout;

};

#endif	/* SHIP_H */

