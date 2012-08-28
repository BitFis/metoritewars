/* 
 * File:   GameOver.h
 * Author: zurcherl
 *
 * Created on 28. August 2012, 09:33
 */

#ifndef GAMEOVER_H
#define	GAMEOVER_H

#include "../../engine/Scene.h"
#include "../../engine/VoidReceiver.h"

class GameOver : public Scene{
public:
  GameOver(World *world);
  virtual void onLoad();
  virtual bool OnEvent(const SEvent& event);
  virtual void onTick();
  virtual void onUnload();
  
private:

};

#endif	/* GAMEOVER_H */

