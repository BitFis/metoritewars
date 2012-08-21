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
  lastshot = 0;
  speed = 0;
  acceleration = 1.0f;
  max_speed = 1.5f;
  
  rotation.set(0.0f);
  current_rotation.set(0.0f);
  rotspeed = 200;
  effective_rotspeed = 1.0f;
  rot_acceleration = 50.0f;
  
  //set material
  if(ship){
    ship->setMaterialFlag(video::EMF_LIGHTING, false);
    ship->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  }
  
  //set Animations
  ship->setFrameLoop(0,39);
  ship->setAnimationSpeed(10);
 /*  
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
  */
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
  // move all shots
  shots->move(DeltaTime);
  float cur_accel = 0.0f;
  bool rotate_side;
  
  
  // calculate current acceleration
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
  
  
  // automaticly slow down spaceship when not accelerating
  if(movement) {
    time_not_accelerating = 0;
  } else {
    time_not_accelerating += DeltaTime;
    float timediff = 0.5f;
    
    int times = time_not_accelerating / timediff;
    if(times > 0) {
      time_not_accelerating -= times * timediff;
      for(int i = 0; i < times; i++) {
        speed *= 0.8f;
      }
    }
  }
  
  // some calculations to not exeed max_speed & have a smooth acceleration
  float new_speed = speed + cur_accel;
  if(abs(new_speed) > abs(speed)) {
    float b = 1 - (speed * speed)/(max_speed * max_speed);
    if(b <= 0) b = DBL_MIN;
    
    float lorentz_factor  = 1/sqrt(b);
    cur_accel /= lorentz_factor;
  }
 
  // accelerate
  speed += cur_accel * DeltaTime;
  
  
  Angle diff(rotation - current_rotation);
  if(diff == Angle(0.0f)) {
    if(diff > M_PI) {
      diff.set(-diff.getDEG() + 360.0f, ANGLE_TYPE_DEG);
      rotate_side = false;
    } else {
      rotate_side = true;
    }

    float cur_rot_accel = rot_acceleration;
    float new_rot_speed = effective_rotspeed + cur_rot_accel;

    if(new_rot_speed > effective_rotspeed) {
      float b = 1 - (effective_rotspeed * effective_rotspeed)/(diff.getDEG() * diff.getDEG());
      if(b <= 0) b = DBL_MIN;

      float lorentz_factor  = 1/sqrt(b);
      cur_rot_accel /= lorentz_factor;
    }

    effective_rotspeed += cur_rot_accel;

    if(rotate_side) {
      current_rotation.set(current_rotation.getDEG() + (diff.getDEG() - effective_rotspeed), ANGLE_TYPE_DEG);
    } else {
      current_rotation.set(current_rotation.getDEG() - (diff.getDEG() - effective_rotspeed), ANGLE_TYPE_DEG);
    }
  }
  
  
  //move forward  
  ship->setPosition(ship->getPosition() + core::vector3df(0.0,0.0,current_rotation.getDEG()).rotationToDirection(core::vector3df(0,speed * DeltaTime,0.0)));
  
  //rotate ship
  ship->setRotation(core::vector3df(90.0,0.0,current_rotation.getDEG()));
}

void Ship::moveFor(){
  movefor = true;
}

void Ship::moveBack(){
  moveback = true;
}

void Ship::rotate(int rotate, float deltaTime){
  rotation.set(rotation.getDEG() - rotspeed * rotate * deltaTime, ANGLE_TYPE_DEG);
}

Shot* Ship::getShots() {
  return shots;
}

Ship::~Ship() {
  delete shots;
}

