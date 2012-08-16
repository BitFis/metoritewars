#ifndef TESTSCENE_H
#define	TESTSCENE_H

#include "../../src/engine/Scene.h"

class TestScene : public Scene {
  
  public: 
    
    bool on_load_called;
    bool on_unload_called;
  
    TestScene(World *world);
    virtual void onLoad();
    virtual bool OnEvent(const SEvent& event);
    virtual void onTick();
    virtual void onUnload();

};

#endif	/* TESTSCENE_H */

