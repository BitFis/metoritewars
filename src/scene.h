
#ifndef _SCENE_H
#define _SCENE_H 1

#include "world.h"
#include <string>

using namespace std;

/* base class for each level or menu or stuff like that
 
   This is basicly just a collection of Object, which are
   used in the same part of the game
   
   for instance: you want to create an new Level
   
    - create a new class and extend this class
    - overwrite the methods on_load(), on_unload()
      and the rest of the virtual methods too. */

class Scene {
  private:
    World *world;
    string name;

  public:
    Scene(string &name);
    void set_world(World *world);

    virtual void on_load() = 0;
    virtual void on_unload() = 0;
}

#endif /* _SCENE_H */
