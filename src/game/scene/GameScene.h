/* 
 * File:   GameScene.h
 * Author: zurcherl
 *
 * Created on 14. August 2012, 17:40
 */

#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "../../engine/Scene.h"
#include "../../engine/VoidReceiver.h"

class GameScene : public Scene{
public:
  GameScene(World *world);
  virtual void onLoad();
  virtual bool OnEvent(const SEvent& event);
  virtual void onTick();
  virtual void onUnload();
  
private:

};

#endif	/* GAMESCENE_H */

