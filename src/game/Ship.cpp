/* 
 * File:   Ship.cpp
 * Author: zurcherl
 * 
 * Created on 16. August 2012, 10:55
 */

#include "Ship.h"

Ship::Ship(const char*  filename, scene::ISceneManager* smgr) {
  ship = smgr->addAnimatedMeshSceneNode(smgr->getMesh(filename),0,12,core::vector3df(0.0,0.0,0.0),core::vector3df(90.0,180.0,0.0),core::vector3df(0.01,0.01,0.01));
  
  shots = new Shot("objects/player/shot.x", smgr, ship);
  
  //set ship variables
  speed = 0;
  movspeed = 1;
  maxSpeed = 2;
  
  rotation = 0;
  rotspeed = 200;
  maxRot = 1;
  
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
  printf("%f / %f \n ", lastshot, passedTime);
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
  ship->setPosition(ship->getPosition() + core::vector3df(0.0,0.0,rotation).rotationToDirection(core::vector3df(0,speed * DeltaTime,0.0)));
  
  //rotate ship
  ship->setRotation(core::vector3df(90.0,0.0,rotation));
  
  
  this->DeltaTime = DeltaTime;
  
  //move ship
  if(movefor){
    if(speed < maxSpeed){
      accelerationSpeed();
    }else{
      speed = maxSpeed;
    }
    
    movefor = false;
  }else{
    speed > 0 && decelerateSpeed();
  }
  
  //rotate ship
  if(moveback){
    if(speed > maxSpeed/5){
      decelerateSpeed();
    }else{
      speed = maxSpeed/5;
    }
    
    moveback = false;
  }
  
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
  speed += 0.1;
}

void Ship::decelerateSpeed(){
  speed -= 0.1;
}

/*void Ship::update(float DeltaTime){
  
  this->DeltaTime = DeltaTime;
  
  //move forward  
  ship->setPosition(ship->getPosition() + core::vector3df(0.0,0.0,rotation).rotationToDirection(core::vector3df(0,speed * DeltaTime,0.0)));
  
  //rotate ship
  ship->setRotation(core::vector3df(90.0,0.0,rotation));
  
  shots->move(DeltaTime);
}

void Ship::autoSlowdown(float* speed, float movspeed, bool* backMovement, bool* forMovement, float DeltaTime){
  float last_speed = *speed;
  
  //reset moveing backwards
  !(*backMovement) && last_speed <= 0 && (*speed = move(movspeed*2, DeltaTime, speed));
  *backMovement = false;
  
  //reset mov forward
  !(*forMovement) && last_speed >= 0 && (*speed = move(-movspeed*2, DeltaTime, speed));
  *forMovement = false;
  
  *speed = ((*speed) > 0 ^ last_speed > 0) ? 0 : (*speed);
}

float Ship::move(int move, float deltaTime, float* speed){

  return *speed + (getAcceleration() * move);
}

void Ship::moveFor(float deltaTime){
  speed = (speed < maxSpeed ? move(movspeed, deltaTime, &speed) : maxSpeed);
  movefor = true;
}

void Ship::moveBack(float deltaTime){
  speed = (speed > -maxSpeed/5 ? move(-movspeed, deltaTime, &speed) : -maxSpeed/5);
  moveback = true;
}

float Ship::getAcceleration(){
  return 0.03;
}

void Ship::rotate(int rotate, float deltaTime){
  //rotate
  rotation -= rotspeed * rotate * deltaTime;
  
  //rotation += rotation < maxRot && rotation > -maxRot ? rotation + rotspeed * rotate * deltaTime : maxRot;
  
  //prevent overflow
}*/

Ship::~Ship() {
  delete shots;
}

