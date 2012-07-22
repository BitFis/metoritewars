#ifndef _WORLD_H
#define _WORLD_H 1

#include "scene.h"
#include <string>


/* this class is responsible for managing
   and switching between scenes */

class World {
  private:
     Scene **scenes;
     unsigned int num_scenes;
     unsigned int current_scene;

     unsigned int get_scene_id(string &name);
     Scene *get_scene_by_id(unsigned int id);


  public:
     World();
     ~World();

     Scene *get_scene(string &name);
     Scene *get_current_scene();

     void add_scene(Scene *scene);
     /* void remove_scene(string &name); @TODO: implement this method */
     void load_scene(string &name);
     void unload_scene(string &name);
};
#endif /* _WORLD_H */
