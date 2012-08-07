#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H 1

#include "Scene.h"
#include <iostream>

using namespace std;

class GameScene : public Scene {
  public: 
    GameScene(World *world);

    virtual void onLoad();
    virtual void onDraw();
    virtual void onUnload();
};

#endif /* _GAME_SCENE_H */
