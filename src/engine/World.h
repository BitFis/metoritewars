#ifndef _WORLD_H
#define _WORLD_H 1

class Scene;

#include "Scene.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "macros.h"
#include <GL/glut.h>
#include <GL/gl.h>


using namespace std;

/* this class is responsible for managing
   and switching between scenes */
class World {

  private:
    static World *instance;
    
    vector<Scene*> *scenes;
    vector<Scene*>::iterator current_scene;
    vector<Scene*>::iterator no_current_scene;

    vector<Scene*>::iterator getSceneIterator(const char *name);
    
    World();

  public:
    
    ~World();

    Scene *getScene(const char *name);
    Scene *getCurrentScene();

    void addScene(Scene *scene);
    void removeScene(Scene *scene);
    void removeScene(const char *name);
    void loadScene(const char *name);
    void unloadScene();
    
    class Guard {
      public: ~Guard() {
        if(World::instance != NULL) {
          delete World::instance;
        }
      }
    };
    friend class Guard;
    
    static World *getInstance();
    
    static void displayCallback(void);
    void delegateDisplay();
    
    
     
};

#ifdef _WORLD_CPP
World *World::instance = NULL;
#endif

#endif /* _WORLD_H */
