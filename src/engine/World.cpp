
#define _WORLD_CPP 15

#include "World.h"
#include "KeyBuffer.h"
#include <iostream>
#include <cstdio>


World::World() {
  this->scenes = new vector<Scene*>(0);
  this->keys = new KeyBuffer();
  this->current_scene = this->no_current_scene = this->scenes->end();
}

World::~World() {
  /* free the pointer array */
  this->scenes->clear();
  delete this->scenes;
  delete this->keys;
}

/*  get the iterator of the scene which
    has the given name */
vector<Scene*>::iterator World::getSceneIterator(const char *name) {
  vector<Scene*>::iterator search;
  /* iterator through all Scene objects */
  for(search = this->scenes->begin(); search != this->scenes->end(); search++) {
    /* compare names */
    if((*search)->getName().compare(string(name)) == 0) {
      break;
    }
  }

  /* throw an exception if the scene doesn't exist */
  if(search == this->scenes->end()) {
    throw invalid_argument("no scene with name '" + string(name) + "'");
  }
  return search;
}

/* get the pointer to the scene object
   which has the given name*/
Scene *World::getScene(const char *name) {
  return *getSceneIterator(name);
}

/* get the currently loaded scene */
Scene *World::getCurrentScene() {
  if(this->current_scene == this->no_current_scene) {
    throw out_of_range("no current scene");
  }
  return *this->current_scene;
}

/* add a scene object to the array of
   scenes in this world */
void World::addScene(Scene *scene) {
  /* check if there already is a scene with the same name  */
  bool exists = false;
  try {
    getSceneIterator(scene->getName().c_str());
    exists = true;
  } catch(invalid_argument &e) {
    /* nope there is none, so add the scene to the array */
    this->scenes->push_back(scene);
  }

  if(exists) {
    /* there is already a scene with the same name, so throw an exception */
    throw invalid_argument("scene '" + scene->getName() + "' has been added before");
  }
}

/* remove a scene by pointer  */
void World::removeScene(Scene *scene) {
  Scene *current = NULL;
  try {
    current = getCurrentScene();
  } catch(out_of_range &ex) { }
  
  foreach(iterator, (*this->scenes)) {
    if(*iterator == scene) {
      if(current == *iterator) {
        unloadScene();
      }
      this->scenes->erase(iterator);
      break;
    }
  }
}

/* remove a scene by name */
void World::removeScene(const char *name) {
  this->scenes->erase(getSceneIterator(name));
}
/* load the scene which has the given name

   the onLoad() method in the Scene object gets called
   if an other scene was loaded before, the
   onUnload()-method gets called too */
void World::loadScene(const char *name) {
  /* unload the old scene (if there is one) */
  unloadScene();

  /* set the new current scene */
  this->current_scene = getSceneIterator(name);

  /* execute the onLoad event in the scene */
  (*this->current_scene)->onLoad();
}

/* this unloads the current loaded scene
   (if there is one)
   
   this also calls the UnloadScene()-method
   on the scene object */
void World::unloadScene() {
  /* unload the old scene */
  try {
    getCurrentScene()->onUnload();
  } catch (out_of_range &e) {}

  /* reset the current scene */
  this->current_scene = this->no_current_scene;
}

World *World::getInstance() {
  static Guard g;
  if(instance == NULL) {
     instance = new World();
  }
  return instance;
}

void World::delegateDisplay() {
  Scene *scene;
  try {
    scene = getCurrentScene();
        
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    //move camera
    glTranslatef(0.0,0.0,-10.0);
    
    scene->onMove();
    
    scene->onDraw();

    glutSwapBuffers();

  } catch (out_of_range &e) {}
}


void World::displayCallback() {
  instance->delegateDisplay();
}

void World::delegateKeyPress(unsigned char key) {
  Scene *scene;
  try {
    scene = getCurrentScene();
    this->keys->set(key, 1);
    scene->onKeyPress(key);
  } catch (out_of_range &e) {}
}
    
void World::keyPressCallback(unsigned char key, int x, int y) {
  instance->delegateKeyPress(key);
}

void World::delegateKeyUp(unsigned char key) {
  Scene *scene;
  try {
    scene = getCurrentScene();
    this->keys->set(key, 0);
    scene->onKeyUp(key);
  } catch (out_of_range &e) {}
}
    
void World::keyUpCallback(unsigned char key, int x, int y) {
  instance->delegateKeyUp(key);
}

void World::delegateMouse(int button, int state, int x, int y) {
  Scene *scene;
  try {
    scene = getCurrentScene();
    scene->onMouseEvent(button, state, x, y);
  } catch (out_of_range &e) {}
}

void World::mouseCallback(int button, int state, int x, int y) {
  instance->delegateMouse(button, state, x, y);
}

KeyBuffer *World::getKeys() {
  return this->keys;
}
