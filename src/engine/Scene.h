
#ifndef _SCENE_H
#define _SCENE_H 1

class World;

#include "World.h"
#include "KeyBuffer.h"
#include "VoidReceiver.h"
#include <string>

#include <irrlicht/irrlicht.h>

using namespace std;
using namespace irr;


/* base class for each level or menu or stuff like that
 
   This is basicly just a collection of Object, which are
   used in the same part of the game
   
   for instance: you want to create an new Level
   
    - create a new class and extend this class
    - overwrite the methods on_load(), on_unload()
      and the rest of the virtual methods too. */

class Scene : public VoidReceiver {
  friend class World;

  protected:
    World *world;
    string name;

  public:
    Scene(const char *name, World *world);
    virtual ~Scene();
    string &getName();

    virtual void onLoad() = 0;
    virtual bool OnEvent(const SEvent& event) = 0;
    virtual void onTick() = 0;
    virtual void onUnload() = 0;

};

#endif /* _SCENE_H */
