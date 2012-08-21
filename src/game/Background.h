/* 
 * File:   Background.h
 * Author: zurcherl
 *
 * Created on 21. August 2012, 09:40
 */

#ifndef Background_H
#define	Background_H

#include <irrlicht/irrlicht.h>
#include <iostream>

using namespace irr;

class Background {
public:
  Background(scene::ISceneManager* smgr, video::IVideoDriver* driver);
  
  void createParticles();
  void stopCreateParticles();
  scene::IParticleSystemSceneNode* returnStars();
  
  virtual ~Background();
private:
  scene::ISceneManager* smgr;

  scene::IParticleEmitter* em;
  scene::IParticleSystemSceneNode* stars;
};

#endif	/* Background_H */

