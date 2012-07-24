#include "world.h"

World::World() {
  this->scenes = new vector<Scene*>(0);
  this->current_scene = this->scenes->end();
}

World::~World() {
  /* free the pointer array */
  unload_scene();
  delete this->scenes;
}

/*  get the iterator of the scene which
    has the given name */
vector<Scene*>::iterator World::get_scene_iterator(const char *name) {
  /* search for the scene */
  string nameobj(name);
  vector<Scene*>::iterator search;
  foreach(iterator, (*this->scenes)) {
    /* compare names */
    if((*iterator)->get_name().compare(nameobj)) {
      search = iterator;
      break;
    }
  }

  /* throw an exception if the scene doesn't exist */
  if(search == this->scenes->end()) {
    string msg("no scene with name '?'");
    size_t pos = msg.find('?');
    throw invalid_argument(msg.replace(pos, pos + 1, name));
  }
  return search;
}

/* get the pointer to the scene object
   which has the given name*/
Scene *World::get_scene(const char *name) {
  return *get_scene_iterator(name);
}

/* get the currently loaded scene */
Scene *World::get_current_scene() {
  if(this->current_scene == this->scenes->end()) {
    throw out_of_range("no current scene");
  }
  return *this->current_scene;
}

/* add a scene object to the array of
   scenes in this world */
void World::add_scene(Scene *scene) {
  /* check if there already is a scene with the same name  */
  bool exists = false;
  try {
    get_scene_iterator(scene->get_name().c_str());
    exists = true;
  } catch(invalid_argument &e) {
    /* nope there is none, so add the scene to the array */
    this->scenes->push_back(scene);
  }

  if(exists) {
    /* there is already a scene with the same name, so throw an exception */
    string msg("scene '?' has been added before");
    size_t pos = msg.find('?');
    throw invalid_argument(msg.replace(pos, pos + 1, scene->get_name()));
  }
}

/* remove a scene by pointer  */
void World::remove_scene(Scene *scene) {
  foreach(iterator, (*this->scenes)) {
    if(*iterator == scene) {
      this->scenes->erase(iterator);
      break;
    }
  }
}

/* remove a scene by name */
void World::remove_scene(const char *name) {
  this->scenes->erase(get_scene_iterator(name));
}
/* load the scene which has the given name

   the on_load() method in the Scene object gets called
   if an other scene was loaded before, the
   on_unload()-method gets called too */
void World::load_scene(const char *name) {
  Scene *current;

  /* unload the old scene (if there is one) */
  unload_scene();

  this->current_scene = get_scene_iterator(name);
  current = *this->current_scene;

  /* execute the on_load event in the scene */
  current->on_load();
}

/* this unloads the current loaded scene
   (if there is one)
   
   this also calls the unload_scene()-method
   on the scene object */
void World::unload_scene() {
  /* unload the old scene */
  try {
    get_current_scene()->on_unload();
  } catch (out_of_range &e) {}

  /* reset the current scene */
  this->current_scene = this->scenes->end();
}
