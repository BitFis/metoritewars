#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "../../engine/Scene.h"
#include "../../engine/VoidReceiver.h"
#include "../Ship.h"
#include "../Meteor.h"

class GameScene : public Scene{
public:
  GameScene(World *world);
  virtual void onLoad();
  virtual bool OnEvent(const SEvent& event);
  virtual void onTick();
  virtual void onUnload();
  
  unsigned int last_meteor_created_at;
  
private:
  Ship *ship;
  vector<Meteor*> *meteors;
};

#endif	/* GAMESCENE_H */

