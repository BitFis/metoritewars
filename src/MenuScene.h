#ifndef _MENU_SCENE_H
#define _MENU_SCENE_H 1

#include "engine/Scene.h"
#include <iostream>

using namespace std;

class MenuScene : public Scene {
  public: 
    MenuScene(World *world);

    virtual void onLoad();
    virtual void onDraw();
    virtual void onUnload();
};

#endif /* _MENU_SCENE_H */
