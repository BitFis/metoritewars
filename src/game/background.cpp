/* 
 * File:   Background.cpp
 * Author: zurcherl
 * 
 * Created on 21. August 2012, 09:40
 */

#include "Background.h"

Background::Background(scene::ISceneManager* smgr, video::IVideoDriver* driver) {
  
  this->smgr = smgr;
  
  scene::IParticleSystemSceneNode* ps =
          smgr->addParticleSystemSceneNode(false);

  stars = ps->createBoxEmitter(
          core::aabbox3d<f32>(-0.7,0.7,-0.7,0.0,0.1,0.7), // emitter size
          core::vector3df(0.0f,0.0f,0.0f),   // initial direction
          800,1000,                             // emit rate
          video::SColor(0,255,255,255),       // darkest color
          video::SColor(0,255,255,255),       // brightest color
          800,2000,0,                         // min and max age, angle
          core::dimension2df(0.f,0.f),         // min size
          core::dimension2df(0.1f,0.1f));        // max size
  
  ps->setEmitter(stars); // this grabs the emitter

  scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

  ps->addAffector(paf); // same goes for the affector
  paf->drop();

  ps->setPosition(core::vector3df(0,0,0));
  ps->setRotation(core::vector3df(0.0,90.0,0.0));
  ps->setScale(core::vector3df(1,3,3));
  ps->setMaterialFlag(video::EMF_LIGHTING, false);
  ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
  ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
  ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}

Background::~Background() {
  
}

