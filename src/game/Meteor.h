#ifndef METEOR_H
#define	METEOR_H

#include <irrlicht/irrlicht.h>
#include "../engine/Angle.h"

using namespace irr;

class Meteor {
private:
  float size;
  unsigned int last_crashed;
  scene::ISceneManager* smgr;
  scene::IAnimatedMeshSceneNode* mesh;
  static scene::IAnimatedMesh* static_mesh;
  float velocity;
  Angle angle;
  
  float calcTransitionTime(float distance);
  void attachRotateAnimator();
  Angle genRandomAngle();
  Angle genRandomAngle(Angle before);
  void loadMesh();
public:
  Meteor(scene::ISceneManager* smgr);
  virtual ~Meteor();
  scene::IAnimatedMeshSceneNode* getMesh();
  bool collidesWith(scene::ISceneNode* node);
  bool tooFarAwayFrom(core::vector3df pos, float distance);
  void bounceOf(Meteor *meteor);
  void setLastCrashed(unsigned int last_crashed);
  unsigned int getLastCrashed();
  void update(float delta);
};

#ifdef _METEOR_CPP
scene::IAnimatedMesh* Meteor::static_mesh = 0;
#endif

#endif	/* METEOR_H */


