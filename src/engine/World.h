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
#include "KeyBuffer.h"


using namespace std;

/* this class is responsible for managing
   and switching between scenes */
class World {

  private:
    static World *instance;
    
    KeyBuffer *keys;
    
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
    
    static void keyPressCallback(unsigned char key, int x, int y);
    void delegateKeyPress(unsigned char key);
    
    static void keyUpCallback(unsigned char key, int x, int y);
    void delegateKeyUp(unsigned char key);
    
    static void mouseCallback(int button, int state, int x, int y);
    void delegateMouse(int button, int state, int x, int y);
    
    KeyBuffer *getKeys();
    
     
};

#ifdef _WORLD_CPP
World *World::instance = NULL;
#endif

#endif /* _WORLD_H */
