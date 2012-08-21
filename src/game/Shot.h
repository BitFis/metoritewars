/* 
 * File:   Shot.h
 * Author: zurcherl
 *
 * Created on 17. August 2012, 13:17
 */

#ifndef Shot_H
#define	Shot_H

#include <irrlicht/irrlicht.h>
#include <vector>

#include "../engine/macros.h"

using namespace irr;

class Shot {
public:
  Shot(const char*  filename, scene::ISceneManager* smgr, scene::IAnimatedMeshSceneNode* ship);
  void createShot(core::vector3df shotpos, core::vector3df shiprot, core::vector3df shipscale);
  void setShotSpeed();
  void move(float DeltaTime);
  
  float getShotTimeout();
  
  std::vector<scene::ISceneNode*> &getShotNode();
  
  void removeShot(std::vector<scene::ISceneNode*>::iterator &shot);
  void removeShot(scene::ISceneNode* shot);
  
  void setShotSpeed(float Speed);
  void setLiveTime(float LiveTime);
  
  virtual ~Shot();
  
private:
  
  scene::ISceneManager* smgr;
  scene::IAnimatedMeshSceneNode* mainShot;
  
  std::vector<scene::ISceneNode*> shots;
  
  float shotspeed;
  float livetime;
  float shottimeout;

};

#endif	/* Shot_H */

