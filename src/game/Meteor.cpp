#include "Meteor.h"

Meteor::Meteor(scene::ISceneManager* smgr) {
  this->smgr = smgr;
  anms = smgr->addAnimatedMeshSceneNode(smgr->getMesh("objects/player/meteor.3ds"), 0, 15, core::vector3df(0.0, 0.0, 0.0), core::vector3df(0.0, 0.0, 0.0), core::vector3df(0.01, 0.01, 0.01));
  
  if(anms) {
    anms->setMaterialFlag(video::EMF_LIGHTING, false);
    scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.3, 0.3, 0.3));
    anms->addAnimator(anim);
    anim->drop();
  }
}

Meteor::~Meteor() {
  anms->drop();
}

