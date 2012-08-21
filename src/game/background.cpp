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

  scene::IParticleEmitter* em = ps->createBoxEmitter(
          core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size
          core::vector3df(0.0f,0.06f,0.0f),   // initial direction
          80,100,                             // emit rate
          video::SColor(0,255,255,255),       // darkest color
          video::SColor(0,255,255,255),       // brightest color
          800,2000,0,                         // min and max age, angle
          core::dimension2df(10.f,10.f),         // min size
          core::dimension2df(20.f,20.f));        // max size

  ps->setEmitter(em); // this grabs the emitter
  em->drop(); // so we can drop it here without deleting it

  scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

  ps->addAffector(paf); // same goes for the affector
  paf->drop();

  ps->setPosition(core::vector3df(-70,60,40));
  ps->setScale(core::vector3df(2,2,2));
  ps->setMaterialFlag(video::EMF_LIGHTING, false);
  ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
  ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
  ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}

Background::~Background() {
  
}

