
#ifndef _SCENE_H
#define _SCENE_H 1

class World;

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
  friend class World;

  private:
    World *world;
    string name;

  public:
    Scene(const char *name, World *world);
    string &get_name();

    virtual void on_load() = 0;
    virtual void on_draw() = 0;
    virtual void on_unload() = 0;

};

#endif /* _SCENE_H */
