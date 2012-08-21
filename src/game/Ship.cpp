/* 
 * File:   Ship.cpp
 * Author: zurcherl
 * 
 * Created on 16. August 2012, 10:55
 */

#include <basetsd.h>

#include "Ship.h"

Ship::Ship(const char*  filename, scene::ISceneManager* smgr, video::IVideoDriver* driver) {
  lastshot = 0;
  ship = smgr->addAnimatedMeshSceneNode(smgr->getMesh(filename),0,12,core::vector3df(0.0,0.0,0.0),core::vector3df(0.0,180.0,0.0),core::vector3df(0.01,0.01,0.01),smgr);
  
  this->driver = driver;
  
  shots = new Shot("objects/player/shot.x", smgr, ship);
  
  //set ship variables
  speed = core::vector3df(0.0f,0.0f,0.0f);
  acceleration = 1.0f;
  maxSpeed = 2;
  
  rotation.set(0.0f);
  rotspeed = 1.0f;
  maxRot = 1;
  
  movefor = false;
  moveback = false;
  
  //set material
  if(ship){
    ship->setMaterialFlag(video::EMF_LIGHTING, false);
    ship->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  }
  
  //set Animations
  ship->setFrameLoop(0,39);
  ship->setAnimationSpeed(10);
  
  //adding particle effect
  shipfire = smgr->addParticleSystemSceneNode(false);
  
  scene::IParticleEmitter* em = shipfire->createBoxEmitter(
          core::aabbox3d<f32>(-0.7,0.7,-0.7,0.0,0.1,0.7), // emitter size
          core::vector3df(0.0f,0.0f,0.0f),   // initial direction
          8000,1000,                             // emit rate
          video::SColor(0,255,255,255),       // darkest color
          video::SColor(0,255,255,255),       // brightest color
          200000,200000,0,                         // min and max age, angle
          core::dimension2df(0.f,0.f),         // min size
          core::dimension2df(0.2f,0.2f));        // max size
  
  shipfire->setEmitter(em);
  
  //em->drop();
  
  shipfire->setMaterialFlag(video::EMF_LIGHTING, false);
  shipfire->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
  shipfire->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
  shipfire->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
  
}

void Ship::shoot(float passedTime){
  if(lastshot + shots->getShotTimeout() < passedTime){
    shots->createShot(ship->getPosition(), ship->getRotation(), ship->getScale());
    
    //reset shot
    lastshot = passedTime;
  }
}
  
core::vector3df Ship::getPosVec3df(){
  return ship->getPosition();
}

scene::ISceneNode* Ship::getShipNode(){
  return ship;
}

void Ship::update(float DeltaTime){  
  //moving shots
  shots->move(DeltaTime);
  
  this->DeltaTime = DeltaTime;
  
  float cur_accel;
  
  bool movement = false;
  
  if(movefor) {
    cur_accel += acceleration;
    movefor = false;
    movement = true;
  }
  if(moveback) {
    cur_accel -= acceleration;
    moveback = false;
    movement = true;
  }
  
  if(!movement) {
    speed *= 0.995f; // @TODO: this should not be indepentent to DeltaTime ...
  }
  
  core::vector3df accel_vec(sin(rotation.getRAD()) * cur_accel * DeltaTime, cos(rotation.getRAD()) * cur_accel * DeltaTime, 0.0f);
  core::vector3df new_speed = speed + accel_vec;
  
  float cur_length = speed.getDistanceFrom(core::vector3df(0,0,0));
  
  if(new_speed.getDistanceFrom(core::vector3df(0,0,0)) > cur_length) {
    float b = 1 - (cur_length * cur_length)/(maxSpeed * maxSpeed);
    if(b <= 0) b = DBL_MIN;
    
    float lorentz_factor  = 1/sqrt(b);
    accel_vec /= lorentz_factor;
  }
  
  speed += accel_vec;
  
  //move forward  
  ship->setPosition(ship->getPosition() + core::vector3df(0.0,0.0,rotation.getDEG()).rotationToDirection(speed * DeltaTime));
  
  //rotate ship
  ship->setRotation(core::vector3df(90.0,0.0,rotation.getDEG()));
}

void Ship::moveFor(float deltaTime){
  //speed = (speed < maxSpeed ? move(movspeed, deltaTime, &speed) : maxSpeed);
  movefor = true;
}

void Ship::moveBack(float deltaTime){
  //speed = (speed > -maxSpeed/5 ? move(-movspeed, deltaTime, &speed) : -maxSpeed/5);
  moveback = true;
}


void Ship::rotate(int rotate, float deltaTime){
  Angle angle(3600.0f + rotspeed * rotate, ANGLE_TYPE_DEG);
  cout << "angle = " << angle.getDEG() << endl;
  rotation -= angle;
}

Shot* Ship::getShots() {
  return shots;
}

Ship::~Ship() {
  delete shots;
}

