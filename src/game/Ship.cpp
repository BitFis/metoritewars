/* 
 * File:   Ship.cpp
 * Author: zurcherl
 * 
 * Created on 16. August 2012, 10:55
 */

#include "Ship.h"

Ship::Ship(char*  filename, scene::ISceneManager* smgr) {
  smgr->addAnimatedMeshSceneNode(smgr->getMesh(filename));
  
}

Ship::~Ship() {
}

