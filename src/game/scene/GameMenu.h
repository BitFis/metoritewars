/* 
 * File:   GameMenu.h
 * Author: zurcherl
 *
 * Created on 14. August 2012, 15:47
 */

#ifndef GAMEMENU_H
#define	GAMEMENU_H

#include "../../engine/Scene.h"
#include "../../engine/VoidReceiver.h"

#define MENU_EXIT_BUTTON 300
#define MENU_START_GAME 301

class GameMenu : public Scene{
public:
  GameMenu(World *world);
  virtual void onLoad();
  virtual bool OnEvent(const SEvent& event);
  virtual void onTick();
  virtual void onUnload();
  
private:

};

#endif	/* GAMEMENU_H */

