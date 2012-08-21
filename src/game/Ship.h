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
  void moveFor();
  void moveBack();
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
  
  float max_speed; //max possible speed
  
  float lastshot; //to set shot timeout
  
  float rotation; //current rotation
  float acceleration;
  float speed; //current move speed
  
  float rotspeed; //rotation boost
  
  bool movefor; //moving forward
  bool moveback; //moving backwards
  
  float time_not_accelerating;

};

#endif	/* SHIP_H */

