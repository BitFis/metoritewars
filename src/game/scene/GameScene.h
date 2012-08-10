/* 
 * File:   GameScene.h
 * Author: zurcherl
 *
 * Created on 9. August 2012, 15:53
 */

#include "../../engine/Model_3DS.h"
#include "../../engine/Scene.h"
#include "../../engine/Timer.h"

#include <iostream>
#include <GL/glu.h>
#include <GL/gl.h>

#ifndef GAMESCENE_H
#define	GAMESCENE_H

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

