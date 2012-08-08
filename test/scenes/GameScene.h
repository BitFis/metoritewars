#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "../../src/Scene.h"

class GameScene {
  public: 
    GameScene();
    ~GameScene();
    virtual void onLoad();
    virtual void onDraw();
    virtual void onUnload();
  private:

};

#endif	/* GAMESCENE_H */

