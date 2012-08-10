/* 
 * File:   GameScene.h
 * Author: zurcherl
 *
 * Created on 9. August 2012, 15:53
 */

#include "../../engine/Model_3DS.h"
#include "../../engine/Scene.h"

#include <iostream>
#include <GL/glu.h>

#ifndef GAMESCENE_H
#define	GAMESCENE_H

class GameScene : public Scene {

  private:
    Model_3DS testobj;
  
  public:
    GameScene(World *world);

    virtual void onLoad();
    virtual void onMove();
    virtual void onDraw();
    virtual void onUnload();

};

#endif	/* GAMESCENE_H */

