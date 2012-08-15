#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "../../src/engine/Scene.h"

class GameScene : public Scene{
  public: 
    GameScene(World *world);
    virtual void onLoad();
    virtual bool OnEvent(const SEvent& event);
    virtual void onTick();
    virtual void onUnload();
};

#endif	/* GAMESCENE_H */

