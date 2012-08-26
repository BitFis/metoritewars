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

using namespace irr;

class Ship {
public:
  Ship(const char*  filename, scene::ISceneManager* smgr, video::IVideoDriver* driver);
  float move(int move, float deltaTime, float* speed);
  void rotate(int rotate, float deltaTime);
  void moveFor();
  void moveBack();
  void update(float DeltaTime);
  
  void shoot(float passedTime);
  
  Shot* getShots();
  
  core::vector3df getPosVec3df();
  scene::ISceneNode* getShipNode();
  Angle getRotation();
  
  virtual ~Ship();
private:
  
  void autoSlowdown(float* speed, float movspeed, bool* backMovement, bool* forMovement, float DeltaTime);
  void createShipFire();
  void removeShipFire();
  
  Shot* shots;
  
  scene::ISceneManager* smgr;
  video::IVideoDriver* driver;
  scene::IAnimatedMeshSceneNode* ship;
  
  scene::IParticleSystemSceneNode* shipfire;
  
  float max_speed; //max possible speed
  
  float lastshot; //to set shot timeout
  
  Angle current_rotation;
  Angle rotation; //current rotation
  float acceleration;
  float speed; //current move speed
  
  float rotspeed;
  float effective_rotspeed;
  float rot_acceleration;
  
  bool movefor; //moving forward
  bool moveback; //moving backwards
  
  float time_not_accelerating;

};

#endif	/* SHIP_H */

