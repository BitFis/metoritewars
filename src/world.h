#ifndef _WORLD_H
#define _WORLD_H 1

class Scene;

#include "scene.h"
#include <string>
#include <vector>
#include "macros.h"

using namespace std;

/* this class is responsible for managing
   and switching between scenes */
class World {

  private:
    vector<Scene*> *scenes;
    vector<Scene*>::iterator current_scene;

    vector<Scene*>::iterator get_scene_iterator(string &name);
    Scene *get_scene_by_iterator(vector<Scene*>::iterator &iterator);


  public:
    World();
    ~World();

    Scene *get_scene(string &name);
    Scene *get_current_scene();

    void add_scene(Scene *scene);
    void remove_scene(Scene *scene);
    void remove_scene(string &name);
    void load_scene(string &name);
    void unload_scene();
     
};

#endif /* _WORLD_H */
