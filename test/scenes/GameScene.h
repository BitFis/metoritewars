#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "GameScene.h"

class GameScene : public Scene {
  public: 
    GameScene(World *world);
    virtual void onLoad();
    virtual void onDraw();
    virtual void onUnload();

};

#endif	/* GAMESCENE_H */

