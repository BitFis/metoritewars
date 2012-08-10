#ifndef _MENU_SCENE_H
#define _MENU_SCENE_H 1

#include "../../engine/Timer.h"
#include "../../engine/Model_3DS.h"
#include "../../engine/Scene.h"
#include "../../engine/soil/SOIL.h"
#include <GL/freeglut_ext.h>
#include <iostream>

using namespace std;

class MenuScene : public Scene {
  private:
    GLint menugui;
    GLint background;
    Model_3DS planet;
    Model_3DS ship;
    Timer timer;
    
  public: 
    MenuScene(World *world);

    virtual void onLoad();
    virtual void onMouseEvent(int button, int state, int x, int y);
    virtual void onKeyPress(unsigned char key);
    virtual void onKeyUp(unsigned char key);
    virtual void onMove();
    virtual void onDraw();
    virtual void onUnload();
};

#endif /* _MENU_SCENE_H */
