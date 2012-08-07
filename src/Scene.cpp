#include "Scene.h"
using namespace std;

Scene::Scene(const char *name, World *world) {
  this->name.assign(name);
  this->world = world;
}

string &Scene::getName() {
  return this->name;
}
