#ifndef _WORLD_H
#define _WORLD_H 1

class Scene;

#include "scene.h"
#include <string>

using namespace std;

/* this class is responsible for managing
   and switching between scenes */
class World {

  private:
    Scene **scenes;
    int num_scenes;
    int current_scene;

    int get_scene_id(string &name);
    Scene *get_scene_by_id(int id);


  public:
    World();
    ~World();

    Scene *get_scene(string &name);
    Scene *get_current_scene();

    void add_scene(Scene *scene);
    /* void remove_scene(string &name); @TODO: implement this method */
    void load_scene(string &name);
    void unload_scene();
     
};

#endif /* _WORLD_H */
