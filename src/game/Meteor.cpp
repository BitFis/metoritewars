#define _METEOR_CPP
#include "Meteor.h"

Meteor::Meteor(scene::ISceneManager* smgr) {
  this->smgr = smgr;
  anim_fly = 0;
  velocity = 0;
  /* load the mesh only once from the disk */
  if(static_mesh == 0)  {
    static_mesh = smgr->getMesh("objects/player/meteor.x");
  }
  /* generate random size */
  size =  sqrt(sqrt((rand() / (float)RAND_MAX) * 100)) / 250;
  
  int force = 100;
  velocity = force / size;
  
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
  float radius = 1.0f;
  
  /* generate a random angle to get a random position on the circle edge */
  Angle angle = genRandomAngle();
  to_anim.set(sin(angle.getRAD()) * radius, cos(angle.getRAD()) * radius, 0);
  
  /* again generate a random angle, but this on should not be near the other 
     generated angle */
  angle = genRandomAngle(angle);
  from_anim.set(sin(angle.getRAD()) * radius, cos(angle.getRAD()) * radius, 0);
  
  /* calculate distance betweed these two points of the circle edge */
  float distance = from_anim.getDistanceFrom(to_anim);
  
  /* create the animation */
  anim_fly = smgr->createFlyStraightAnimator(from_anim, to_anim, calcTransitionTime(distance), false, false);
  mesh->addAnimator(anim_fly);
}


float Meteor::calcTransitionTime(float distance) {
  return (distance / velocity) * 25000000;
}

void Meteor::attachFlightAnimator(float angle) {
  /* define the radius of the circle arround the camera where meteorids
     are spawned in*/
  float radius = 1.0f;
  
  
  u32 time_left = calcTransitionTime(mesh->getPosition().getDistanceFrom(to_anim));
  
  /* calculate the coords for the new angle */
  to_anim.set(sin(angle) * radius, cos(angle) * radius, 0);
  from_anim.set(mesh->getPosition());
  mesh->removeAnimator(anim_fly);
  
  
  /* create the animation */
  anim_fly = smgr->createFlyStraightAnimator(from_anim, to_anim, time_left, false, false);
  
  mesh->addAnimator(anim_fly);
  
}

Angle Meteor::genRandomAngle() {
  /* generate random angle in RAD */
  return Angle(((rand() / (float)RAND_MAX) * 360) / 180 * M_PI);
}

Angle Meteor::genRandomAngle(Angle before) {
  /* generate random angle in RAD but it should not be near `before` */
  Angle angle(0.0f), upper(0.0f), lower(0.0f);
  do {
    angle = genRandomAngle();
    upper = angle + M_PI_4;
    lower = angle - M_PI_4;
  } while(before < upper && before > lower);
  return angle;
}

scene::IAnimatedMeshSceneNode* Meteor::getMesh() {
  return mesh;
}


bool Meteor::collidesWith(scene::ISceneNode* node) {
  /* check if the bounding boxes collide */
  return node->getTransformedBoundingBox().intersectsWithBox(this->mesh->getTransformedBoundingBox());
}

void Meteor::bounceOf(Meteor* meteor) {
  /* core::vector3df pos1 = this->mesh->getPosition();
  core::vector3df pos2 = meteor->getMesh()->getPosition();
  
  float angle = acos(abs(this->mesh->getPosition().Y - this->to_anim.Y) / this->mesh->getPosition().getDistanceFrom(this->to_anim));
  
  cout << angle / M_PI * 180 << endl;
  
  
  if(abs(pos1.X - pos2.X) < abs(pos1.Y - pos2.Y)) {
    //vertical
    angle = angle > M_PI ? M_PI - (angle - M_PI) + M_PI : M_PI - angle;
  } else {
    
    angle -= M_PI_2;
    if(angle < 0) {
      angle = M_2_PI - angle;
    }
    angle = M_PI - (angle - M_PI) + M_PI;
    if(angle > M_2_PI) {
      angle -= M_2_PI;
    }
    angle += M_PI_2;
  }
  
  cout << angle / M_PI * 180 << endl;
  
  attachFlightAnimator(angle); */
}

bool Meteor::animationFinished() {
  return anim_fly->hasFinished();
}

Meteor::~Meteor() {
  anim_fly->drop();
  mesh->drop();
  mesh->removeAll();
}
