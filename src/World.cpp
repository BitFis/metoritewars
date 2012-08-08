#include "World.h"
#include <iostream>

World::World() {
  this->scenes = new vector<Scene*>(0);
  this->current_scene = this->scenes->end();
}

World::~World() {
  /* free the pointer array */
  unloadScene();
  delete this->scenes;
}

/*  get the iterator of the scene which
    has the given name */
vector<Scene*>::iterator World::getSceneIterator(const char *name) {
  /* search for the scene */
  string nameobj(name);
  vector<Scene*>::iterator search = this->scenes->end();
  foreach(iterator, (*this->scenes)) {
    /* compare names */
    if((*iterator)->getName().compare(nameobj) == 0) {
      search = iterator;
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
  if(this->current_scene == this->scenes->end()) {
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
  foreach(iterator, (*this->scenes)) {
    if(*iterator == scene) {
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

   the on_load() method in the Scene object gets called
   if an other scene was loaded before, the
   on_unload()-method gets called too */
void World::loadScene(const char *name) {
  Scene *current;

  /* unload the old scene (if there is one) */
  unloadScene();

  this->current_scene = getSceneIterator(name);
  current = *this->current_scene;

  /* execute the on_load event in the scene */
  current->onLoad();
}

/* this unloads the current loaded scene
   (if there is one)
   
   this also calls the unload_scene()-method
   on the scene object */
void World::unloadScene() {
  /* unload the old scene */
  try {
    getCurrentScene()->onUnload();
  } catch (out_of_range &e) {}

  /* reset the current scene */
  this->current_scene = this->scenes->end();
}