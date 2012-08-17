#define _METEOR_CPP
#include "Meteor.h"

Meteor::Meteor(scene::ISceneManager* smgr) {
  this->smgr = smgr;
  if(static_mesh == 0)  {
    static_mesh = smgr->getMesh("objects/player/meteor.x");
  }
  
  size = sqrt(sqrt((rand() / (float)RAND_MAX) * 100)) / 250;
  mesh = smgr->addAnimatedMeshSceneNode(static_mesh, 0, 15, core::vector3df(0.0, 0.0, 0.0), core::vector3df(0.0, 0.0, 0.0), core::vector3df(size, size, size));
  
  if(mesh) {
    mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    attachFlightAnimator();
    attachRotateAnimator();
  }
}

void Meteor::attachRotateAnimator() {
  float rotatex = (rand() / (float)RAND_MAX) * 0.8f - 0.4f;
  float rotatey = (rand() / (float)RAND_MAX) * 0.8f - 0.4f;
  float rotatez = (rand() / (float)RAND_MAX) * 0.8f - 0.4f;
  scene::ISceneNodeAnimator* anim_rotate = smgr->createRotationAnimator(core::vector3df(rotatex, rotatey, rotatez));
  mesh->addAnimator(anim_rotate);
  anim_rotate->drop();
}

void Meteor::attachFlightAnimator() {
  float radius = 1.5f;
  float angle = genRandomAngle();
  float x1 = sin(angle) * radius;
  float y1 = cos(angle) * radius;
  angle = genRandomAngle(angle);
  float x2 = sin(angle) * radius;
  float y2 = cos(angle) * radius;
  float distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / (radius * 2);
  u32 time = (4000 * distance) * (size * 150);
  scene::ISceneNodeAnimator* anim_delete = smgr->createDeleteAnimator(time);
  mesh->addAnimator(anim_delete);
  anim_delete->drop();
  scene::ISceneNodeAnimator* anim_fly = smgr->createFlyStraightAnimator(core::vector3df(x1, y1, 0.0), core::vector3df(x2, y2, 0.0), time, false, false);
  mesh->addAnimator(anim_fly);
  anim_fly->drop();
}

float Meteor::genRandomAngle() {
  return ((rand() / (float)RAND_MAX) * 360) / 180 * M_PI;
}

float Meteor::genRandomAngle(float before) {
  float angle, upper, lower;
  bool ok = false;
  while(!ok) {
    angle = genRandomAngle();
    upper = angle + M_PI_4;
    lower = angle - M_PI_4;
    if(!(before < upper && before > lower)) {
      before = before + M_PI;
      before = before > M_2_PI ? before - M_2_PI : before;
      upper = upper + M_PI;
      upper = upper > M_2_PI ? upper - M_2_PI : upper;
      lower = lower + M_PI;
      lower = lower > M_2_PI ? lower - M_2_PI : lower;
      if(!(before < upper && before > lower)) {
        ok = true;
      }
    }
  }
  return angle;
}

Meteor::~Meteor() {
  mesh->drop();
  mesh->removeAll();
}

