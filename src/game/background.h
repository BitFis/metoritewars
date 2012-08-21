/* 
 * File:   Background.h
 * Author: zurcherl
 *
 * Created on 21. August 2012, 09:40
 */

#ifndef Background_H
#define	Background_H

#include <irrlicht/irrlicht.h>

using namespace irr;

class Background {
public:
  Background(scene::ISceneManager* smgr, video::IVideoDriver* driver);
  virtual ~Background();
private:
  scene::ISceneManager* smgr;

};

#endif	/* Background_H */

