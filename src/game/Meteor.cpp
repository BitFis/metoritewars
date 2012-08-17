#define _METEOR_CPP
#include "Meteor.h"

Meteor::Meteor(scene::ISceneManager* smgr) {
  this->smgr = smgr;
  anim_fly = 0;
  
  /* load the mesh only once from the disk */
  if(static_mesh == 0)  {
    static_mesh = smgr->getMesh("objects/player/meteor.x");
  }
  /* generate random size */
  size = sqrt(sqrt((rand() / (float)RAND_MAX) * 100)) / 250;
  
  /* create the animated mesh */
  mesh = smgr->addAnimatedMeshSceneNode(static_mesh, 0, 15, core::vector3df(0.0, 0.0, 0.0), core::vector3df(0.0, 0.0, 0.0), core::vector3df(size, size, size));
  
  /* attach lightning and animation stuff */
  if(mesh) {
    mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    attachFlightAnimator();
    attachRotateAnimator();
  }
}

void Meteor::attachRotateAnimator() {
  /* generate random coordinates for rotatino*/
  float rotatex = (rand() / (float)RAND_MAX) * 0.8f - 0.4f;
  float rotatey = (rand() / (float)RAND_MAX) * 0.8f - 0.4f;
  float rotatez = (rand() / (float)RAND_MAX) * 0.8f - 0.4f;
  
  /* create animation and attach it to the mesh */
  scene::ISceneNodeAnimator* anim_rotate = smgr->createRotationAnimator(core::vector3df(rotatex, rotatey, rotatez));
  mesh->addAnimator(anim_rotate);
  anim_rotate->drop();
}

void Meteor::attachFlightAnimator() {
  /* define the radius of the circle arround the camera where meteorids
     are spawned in*/
  float radius = 1.5f;
  
  /* generate a random angle to get a random position on the circle edge */
  float angle = genRandomAngle();
  float x1 = sin(angle) * radius;
  float y1 = cos(angle) * radius;
  
  /* again generate a random angle, but this on should not be near the other 
     generated angle */
  angle = genRandomAngle(angle);
  float x2 = sin(angle) * radius;
  float y2 = cos(angle) * radius;
  
  /* calculate distance betweed these two points of the circle edge */
  float distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / (radius * 2);
  
  /* create the animation */
  anim_fly = smgr->createFlyStraightAnimator(core::vector3df(x1, y1, 0.0), core::vector3df(x2, y2, 0.0), (4000 * distance) * (size * 150), false, false);
  mesh->addAnimator(anim_fly);
  
}

float Meteor::genRandomAngle() {
  /* generate random angle in RAD */
  return ((rand() / (float)RAND_MAX) * 360) / 180 * M_PI;
}

float Meteor::genRandomAngle(float before) {
  /* generate random angle in RAD but it should not be near `before` */
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

scene::IAnimatedMeshSceneNode* Meteor::getMesh() {
  return mesh;
}


bool Meteor::collidesWith(scene::ISceneNode* node) {
  /* check if the bounding boxes collide */
  return node->getTransformedBoundingBox().intersectsWithBox(this->mesh->getTransformedBoundingBox());
}

bool Meteor::animationFinished() {
  return anim_fly->hasFinished();
}

Meteor::~Meteor() {
  anim_fly->drop();
  mesh->drop();
  mesh->removeAll();
}

