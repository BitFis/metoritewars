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
#include <cmath>

using namespace irr;

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
  
  core::vector3df getPosVec3df();
  scene::ISceneNode* getShipNode();
  
  virtual ~Ship();
private:
  void accelerationSpeed();
  void decelerateSpeed();
  
  void autoSlowdown(float* speed, float movspeed, bool* backMovement, bool* forMovement, float DeltaTime);
  
  Shot* shots;
  
  scene::ISceneManager* smgr;
  scene::IAnimatedMeshSceneNode* ship;
  
  float DeltaTime;
  
  float maxSpeed; //max possible speed
  float maxRot; //max rotation
  
  float lastshot = 0; //to set shot timeout
  
  float rotation; //current rotation
  float speed; //current move speed
  
  float movspeed; //move boost
  float rotspeed; //rotation boost
  
  bool movefor; //moving forward
  bool moveback; //moving backwards
  
  bool rotright; //right rotation
  bool rotleft; //left rotation
  
  float timeout;

};

#endif	/* SHIP_H */

