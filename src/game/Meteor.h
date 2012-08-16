#ifndef METEOR_H
#define	METEOR_H

#include <irrlicht/irrlicht.h>

using namespace irr;

class Meteor {
private:
  scene::ISceneManager* smgr;
  scene::IAnimatedMeshSceneNode* anms;
  
public:
  Meteor(scene::ISceneManager* smgr);
  virtual ~Meteor();


};

#endif	/* METEOR_H */

