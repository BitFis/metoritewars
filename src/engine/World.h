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


#include <irrlicht/irrlicht.h>


using namespace std;
using namespace irr;

/* this class is responsible for managing
   and switching between scenes */
class World : public IEventReceiver {

  private:
    IrrlichtDevice *device;
    
    KeyBuffer *keys;
    
    vector<Scene*> *scenes;
    vector<Scene*>::iterator current_scene;
    vector<Scene*>::iterator no_current_scene;

    vector<Scene*>::iterator getSceneIterator(const char *name);
    
  public:
        
    World(IrrlichtDevice *device);
    ~World();

    // methods to add, remove, load & unload scenes
    Scene *getScene(const char *name);
    Scene *getCurrentScene();

    void addScene(Scene *scene);
    void removeScene(Scene *scene);
    void removeScene(const char *name);
    void loadScene(const char *name);
    void unloadScene();
    
    // methods needed to receive and delgate event
    bool OnEvent(const SEvent& event);
    
    IrrlichtDevice* getDevice();
    
    KeyBuffer *getKeys();
     
};
#endif /* _WORLD_H */
