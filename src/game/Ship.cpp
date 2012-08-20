/* 
 * File:   Ship.cpp
 * Author: zurcherl
 * 
 * Created on 16. August 2012, 10:55
 */

#include "Ship.h"

Ship::Ship(const char*  filename, scene::ISceneManager* smgr) {
  ship = smgr->addAnimatedMeshSceneNode(smgr->getMesh(filename),0,12,core::vector3df(0.0,0.0,0.0),core::vector3df(-90.0,0.0,0.0),core::vector3df(0.01,0.01,0.01));
  
  //set ship variables
  speed = 0;
  movspeed = 1;
  maxSpeed = 0.04;
  
  rotation = 0;
  rotspeed = 150;
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

void Ship::update(float DeltaTime){
  //move forward
  ship->setPosition(core::vector3df((speed * sinf(2 * core::PI / 360 * rotation)), -(speed * cosf(2 * core::PI / 360 * rotation)),0.0) + ship->getPosition());
  
  //rotate ship
  ship->setRotation(core::vector3df(-90.0,0.0,rotation));
  
  //slowdown movement
  //autoSlowdown(&speed, movspeed, &moveback, &movefor, DeltaTime);
  
  //slowdown rotation
  //autoSlowdown(&rotation, rotspeed, &rotright, &rotleft, DeltaTime);
  
  printf("%f\n", speed);
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

  return *speed + (getAcceleration() * move) * deltaTime;
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
  return 0.05;
}

void Ship::rotate(int rotate, float deltaTime){
  //rotate
  rotation -= rotspeed * rotate * deltaTime;
  
  //rotation += rotation < maxRot && rotation > -maxRot ? rotation + rotspeed * rotate * deltaTime : maxRot;
  
  printf("%f\n", rotation);
  
  //prevent overflow
}

Ship::~Ship() {
}

