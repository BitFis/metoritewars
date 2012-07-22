#include "scene.h"

Scene::Scene(string &name) {
  this->name.assign(name);
}

Scene::setWorld(World *world) {
  this->world = world;
}
