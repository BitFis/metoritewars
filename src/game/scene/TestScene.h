/* 
 * File:   TestScene.h
 * Author: zurcherl
 *
 * Created on 9. August 2012, 16:25
 */

#ifndef TESTSCENE_H
#define	TESTSCENE_H

#include "../../engine/Model_3DS.h"
#include "../../engine/Scene.h"
#include "../../engine/Timer.h"

#include <iostream>
#include <GL/glu.h>

class TestScene : public Scene {
public:
  private:
    Model_3DS testobj;
    double timer;
    Timer time;
    int counter = 0;
     
  public:
    TestScene(World *world);

    virtual void onLoad();
    virtual void onMove();
    virtual void onDraw();
    virtual void onUnload();
private:

};

#endif	/* TESTSCENE_H */

