#ifndef _WORLD_H
#define _WORLD_H 1

class Scene;

#include "Scene.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "macros.h"

using namespace std;

/* this class is responsible for managing
   and switching between scenes */
class World {

  private:
    
    vector<Scene*>::iterator current_scene;
    vector<Scene*>::iterator no_current_scene;

    vector<Scene*>::iterator getSceneIterator(const char *name);

  public:
    vector<Scene*> *scenes;
    World();
    ~World();

    Scene *getScene(const char *name);
    Scene *getCurrentScene();

    void addScene(Scene *scene);
    void removeScene(Scene *scene);
    void removeScene(const char *name);
    void loadScene(const char *name);
    void unloadScene();
     
};

#endif /* _WORLD_H */
