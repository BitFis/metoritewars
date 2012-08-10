#ifndef GAMESCENE_H
#define	GAMESCENE_H


#include "../../engine/Model_3DS.h"
#include "../../engine/Scene.h"
#include "../../engine/Timer.h"

#include <GL/freeglut_ext.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>


#include <iostream>

class GameScene : public Scene {

  private:
    Model_3DS testobj;
    Timer timer;
  
  public:
    GameScene(World *world);

    virtual void onLoad();
    virtual void onMouseEvent(int button, int state, int x, int y);
    virtual void onKeyPress(unsigned char key);
    virtual void onKeyUp(unsigned char key);
    virtual void onMove();
    virtual void onDraw();
    virtual void onUnload();

};

#endif	/* GAMESCENE_H */

