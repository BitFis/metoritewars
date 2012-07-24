#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H 1

#include "scene.h"
#include <iostream>

using namespace std;

class GameScene : public Scene {
  public: 
    GameScene(World *world);

    virtual void on_load();
    virtual void on_draw();
    virtual void on_unload();
};

#endif /* _GAME_SCENE_H */
