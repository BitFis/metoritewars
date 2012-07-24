#ifndef _MENU_SCENE_H
#define _MENU_SCENE_H 1

#include "scene.h"
#include <iostream>

using namespace std;

class MenuScene : public Scene {
  public: 
    MenuScene(World *world);

    virtual void on_load();
    virtual void on_draw();
    virtual void on_unload();
};

#endif /* _MENU_SCENE_H */
