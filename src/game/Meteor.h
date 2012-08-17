#ifndef METEOR_H
#define	METEOR_H

#include <irrlicht/irrlicht.h>
#include <iostream>

using namespace std;
using namespace irr;

class Meteor {
private:
  float size;
  scene::ISceneManager* smgr;
  scene::IAnimatedMeshSceneNode* mesh;
  static scene::IAnimatedMesh* static_mesh;
  
  scene::ISceneNodeAnimator* anim_fly;
  
  void attachFlightAnimator();
  void attachRotateAnimator();
  float genRandomAngle();
  float genRandomAngle(float before);
  void loadMesh();
public:
  Meteor(scene::ISceneManager* smgr);
  virtual ~Meteor();
  scene::IAnimatedMeshSceneNode* getMesh();
  bool collidesWith(scene::ISceneNode* node);
  bool animationFinished();

};

#ifdef _METEOR_CPP
scene::IAnimatedMesh* Meteor::static_mesh = 0;
#endif

#endif	/* METEOR_H */

