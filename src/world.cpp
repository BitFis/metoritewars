#include "world.h"

World::World() {
  this->scenes = new vector<Scene*>(0);
}

World::~World() {
  /* free the pointer array */
  delete this->scenes;
}

/*  get the iterator of the scene which
    has the given name */
vector<Scene*>::iterator World::get_scene_iterator(string &name) {
  /* TODO: what if the scene with the given name
           doesn't exists (currently an exception is thrown) */
  vector<Scene*>::iterator search;
  foreach(iterator, (*this->scenes)) {
    if((*iterator)->get_name().compare(name)) {
      search = iterator;
      break;
    }
  }
  return search;
}

/* get the pointer to the scene object
   which has the given name*/
Scene *World::get_scene(string &name) {
  return *get_scene_iterator(name);
}

/* get the currently loaded scene */
Scene *World::get_current_scene() {
  /* @TODO: what if there is no current scene  */
  return get_scene_by_iterator(this->current_scene);
}

/* add a scene object to the array of
   scenes in this world */
void World::add_scene(Scene *scene) {
  /* @TODO: what if we have to scenes with the same name? */
  this->scenes->push_back(scene);
}

/* remove a scene by pointer  */
void World::remove_scene(Scene *scene) {
  /* @TODO: what if the scene is currently loaded? */
  foreach(iterator, (*this->scenes)) {
    if(*iterator == scene) {
      this->scenes->erase(iterator);
      break;
    }
  }
}

/* remove a scene by name */
void World::remove_scene(string &name) {
  /* @TODO: what if the scene is currently loaded? */
  this->scenes->erase(get_scene_iterator(name));
}
/* load the scene which has the given name

   the on_load() method in the Scene object gets called
   if an other scene was loaded before, the
   on_unload()-method gets called too */
void World::load_scene(string &name) {
  Scene *current;

  /* unload the old scene (if there is one) */
  unload_scene();

   
  /* @TODO: what if there is no Scene which has the given name? */
  this->current_scene = get_scene_iterator(name);
  current = get_scene_by_iterator(this->current_scene);

  /* execute the on_load event in the scene */
  current->on_load();
}

/* this unloads the current loaded scene
   (if there is one)
   
   this also calls the unload_scene()-method
   on the scene object */
void World::unload_scene() {
  /* unload the old scene */
  Scene *current = get_current_scene();
  if(current) {
    current->on_unload();
  }

  /* reset the current scene */
  this->current_scene = --this->scenes->begin();
}
