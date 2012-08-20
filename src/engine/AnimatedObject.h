/* 
 * File:   AnimatedObject.h
 * Author: zurcherl
 *
 * Created on 17. August 2012, 15:40
 */

#ifndef ANIMATEDOBJECT_H
#define	ANIMATEDOBJECT_H

#include <irrlicht/irrlicht.h>

using namespace irr;

class AnimatedObject : public scene::IAnimatedMeshSceneNode {
public:
  
  class localTransform{
    public:
      void Pos(core::vector3df pos);
      void Rot(core::vector3df rot);
      void Scale(core::vector3df scale);

    private:
    
  };
  
private:

};

#endif	/* ANIMATEDOBJECT_H */

