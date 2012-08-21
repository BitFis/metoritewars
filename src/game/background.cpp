/* 
 * File:   Background.cpp
 * Author: zurcherl
 * 
 * Created on 21. August 2012, 09:40
 */

#include "Background.h"

Background::Background(scene::ISceneManager* smgr, video::IVideoDriver* driver) {
  
  this->smgr = smgr;
  
  stars = smgr->addParticleSystemSceneNode(false);

  em = stars->createBoxEmitter(
          core::aabbox3d<f32>(-0.7,0.7,-0.7,0.0,0.1,0.7), // emitter size
          core::vector3df(0.0f,0.0f,0.0f),   // initial direction
          800,1000,                             // emit rate
          video::SColor(0,255,255,255),       // darkest color
          video::SColor(0,255,255,255),       // brightest color
          2000,2000,0,                         // min and max age, angle
          core::dimension2df(0.0f,0.0f),         // min size
          core::dimension2df(0.01f,0.01f));        // max size
  
  stars->setEmitter(em); // this grabs the emitter
  
  
  
  scene::IParticleAffector* paf = stars->createFadeOutParticleAffector();

  stars->addAffector(paf); // same goes for the affector
  paf->drop();

  stars->setRotation(core::vector3df(0.0,0.0,0.0));
  stars->setScale(core::vector3df(7.0,6.0,0.1));
  stars->setPosition(core::vector3df(2.0,-4.0,0.0));
  stars->setMaterialFlag(video::EMF_LIGHTING, false);
  stars->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
  stars->setMaterialTexture(0, driver->getTexture("objects/player/star.png"));
  stars->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
 
}


void Background::createParticles(){
  
  em->setMaxParticlesPerSecond(800);
  em->setMinParticlesPerSecond(1000);
  
  stars->setEmitter(em);
}

scene::IParticleSystemSceneNode* Background::returnStars(){
  return stars;
}

void Background::stopCreateParticles(){
  
  em->setMaxParticlesPerSecond(0);
  em->setMinParticlesPerSecond(0);
  
  stars->setEmitter(em);
}

Background::~Background() {
  em->drop();
  stars->drop();
}

