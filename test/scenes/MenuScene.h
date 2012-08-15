#ifndef MENUSCENE_H
#define	MENUSCENE_H

#include "../../src/engine/Scene.h"

class MenuScene : public Scene {
  public: 
    MenuScene(World *world);
    virtual void onLoad();
    virtual bool OnEvent(const SEvent& event);
    virtual void onTick();
    virtual void onUnload();
};

#endif	/* MENUSCENE_H */

