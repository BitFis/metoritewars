#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "../../engine/Scene.h"
#include "../../engine/VoidReceiver.h"
#include "../Ship.h"
#include "../Meteor.h"
#include "../Background.h"

class GameScene : public Scene{
public:
  GameScene(World *world);
  virtual void onLoad();
  virtual bool OnEvent(const SEvent& event);
  virtual void onTick();
  virtual void onUnload();
  
  
  bool tooFarAwayFrom(scene::IAnimatedMeshSceneNode* mesh, core::vector3df pos, float distance);
  bool tooFarAwayFrom(scene::ISceneNode* mesh, core::vector3df pos, float distance);
  
  unsigned int last_meteor_created_at;
  
private:
  Background* background;
  
  Ship *ship;
  vector<Meteor*> *meteors;
  scene::ICameraSceneNode* camera;
  scene::ILightSceneNode* light;
};

#endif	/* GAMESCENE_H */

