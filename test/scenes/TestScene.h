#ifndef TESTSCENE_H
#define	TESTSCENE_H

#include "../../src/engine/Scene.h"

class TestScene : public Scene {
  public: 
    TestScene(World *world);
    virtual void onLoad();
    virtual void onMove();
    virtual void onDraw();
    virtual void onUnload();

};

#endif	/* TESTSCENE_H */

