#include "World.h"
#include <iostream>
#include <cstdio>

World::World() {
  this->scenes = new vector<Scene*>(0);
  this->current_scene = this->no_current_scene = this->scenes->end();
}

World::~World() {
  /* free the pointer array */
  unloadScene();
  this->scenes->clear();
  delete this->scenes;
}

/*  get the iterator of the scene which
    has the given name */
vector<Scene*>::iterator World::getSceneIterator(const char *name) {
  vector<Scene*>::iterator search;
  /* iterator through all Scene objects*
  for(search = this->scenes->begin(); search != this->scenes->end(); search++) {
    /* compare names *
    if((*search)->getName().compare(string(name)) == 0) {
      break;
    }
  }*/

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
  cout << "removing scene " << scene->getName() << "..." << endl;
  try {
    current = getCurrentScene();
  } catch(out_of_range &ex) { }
  
  foreach(iterator, (*this->scenes)) {
    if(*iterator == scene) {
      // unload current scene if currently loaded
      if(current == *iterator) {
        cout << "unloading scene while removing " << endl;
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
  cout << "loading scene " << name << "..." << endl;
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
  Scene *scene;
  try {
    scene = getCurrentScene();
    
    printf("this->current_scene: %p\n", this->current_scene);
    cout << scene->getName() << endl;
    scene->onLoad();
    
  } catch (out_of_range &e) {}

  /* reset the current scene */
  this->current_scene = this->no_current_scene;
}
