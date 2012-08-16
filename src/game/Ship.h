/* 
 * File:   Ship.h
 * Author: zurcherl
 *
 * Created on 16. August 2012, 10:55
 */

#ifndef SHIP_H
#define	SHIP_H

#include <irrlicht/irrlicht.h>

using namespace irr;

class Ship {
public:
  Ship(char* filename, scene::ISceneManager* smgr);
  virtual ~Ship();
private:
  scene::ISceneManager* smgr;

};

#endif	/* SHIP_H */

