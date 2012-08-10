#ifndef MENUSCENE_H
#define	MENUSCENE_H

#include "../../src/engine/Scene.h"

class MenuScene : public Scene {
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

#endif	/* MENUSCENE_H */

