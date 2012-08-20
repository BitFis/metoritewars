/* 
 * File:   Ship.cpp
 * Author: zurcherl
 * 
 * Created on 16. August 2012, 10:55
 */

#include "Ship.h"

Ship::Ship(const char*  filename, scene::ISceneManager* smgr) {
  lastshot = 0;
  ship = smgr->addAnimatedMeshSceneNode(smgr->getMesh(filename),0,12,core::vector3df(0.0,0.0,0.0),core::vector3df(0.0,180.0,0.0),core::vector3df(0.01,0.01,0.01));
  
  shots = new Shot("objects/player/shot.x", smgr, ship);
  
  //set ship variables
  speed = core::vector3df(0.0f,0.0f,0.0f);
  acceleration = 1.0f;
  maxSpeed = 2;
  
  rotation.set(0);
  rotspeed = 10.0f;
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
  
  //move forward  
  ship->setPosition(ship->getPosition() + core::vector3df(0.0,0.0,rotation.getDEG()).rotationToDirection(speed * DeltaTime));
  
  //rotate ship
  ship->setRotation(core::vector3df(90.0,0.0,rotation.getDEG()));
  
  
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
  
  cout << "speed: " << new_speed.getDistanceFrom(core::vector3df(0,0,0)) << endl;
}

void Ship::moveFor(float deltaTime){
  //speed = (speed < maxSpeed ? move(movspeed, deltaTime, &speed) : maxSpeed);
  movefor = true;
}

void Ship::moveBack(float deltaTime){
  //speed = (speed > -maxSpeed/5 ? move(-movspeed, deltaTime, &speed) : -maxSpeed/5);
  moveback = true;
}

void Ship::accelerationSpeed(){
  speed += (1 * DeltaTime) / sqrt(sqrt(1 / maxSpeed));
}

void Ship::decelerateSpeed(){
  speed -= (1 * DeltaTime) / (1 / sqrt(sqrt(1 / maxSpeed)));
}


void Ship::rotate(int rotate, float deltaTime){
  //rotate
  Angle angle(rotspeed * rotate * deltaTime, ANGLE_TYPE_DEG);
  cout << "angle = " << angle.getDEG() << endl;
  rotation -= angle;
}

Ship::~Ship() {
  delete shots;
}

