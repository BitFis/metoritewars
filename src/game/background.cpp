/* 
 * File:   Background.cpp
 * Author: zurcherl
 * 
 * Created on 21. August 2012, 09:40
 */

#include "Background.h"

Background::Background(scene::ISceneManager* smgr, video::IVideoDriver* driver) {
  
  this->smgr = smgr;
  
  stars =
          smgr->addParticleSystemSceneNode(false);

  scene::IParticleEmitter* em = stars->createBoxEmitter(
          core::aabbox3d<f32>(-0.7,0.7,-0.7,0.0,0.1,0.7), // emitter size
          core::vector3df(0.0f,0.0f,0.0f),   // initial direction
          8000,1000,                             // emit rate
          video::SColor(0,255,255,255),       // darkest color
          video::SColor(0,255,255,255),       // brightest color
          200000,200000,0,                         // min and max age, angle
          core::dimension2df(0.f,0.f),         // min size
          core::dimension2df(0.2f,0.2f));        // max size
  
  stars->setEmitter(em); // this grabs the emitter
  
  scene::IParticleAffector* paf = stars->createFadeOutParticleAffector();

  //stars->addAffector(paf); // same goes for the affector
  paf->drop();

  stars->setPosition(core::vector3df(0,0,0));
  stars->setRotation(core::vector3df(0.0,90.0,0.0));
  stars->setScale(core::vector3df(1,3,3));
  stars->setMaterialFlag(video::EMF_LIGHTING, false);
  stars->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
  stars->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
  stars->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
  
  stars->removeAllAffectors();
 
}

Background::~Background() {
  
}

