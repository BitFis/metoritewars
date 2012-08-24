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
  effective_rotspeed = 0.0f;
  rot_acceleration = 40.0f;
  
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
  
  
  //moving shots
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
  if(!(diff == Angle(0.0f))) {
    float cur_rot_accel;
    if(diff > M_PI) {
      diff.set(360.0f - diff.getDEG(), ANGLE_TYPE_DEG);
      cur_rot_accel = rot_acceleration;
    } else {
      cur_rot_accel = -rot_acceleration;
    }
    
    float new_rot_speed = effective_rotspeed + cur_rot_accel;

    if(abs(new_rot_speed) > abs(effective_rotspeed)) {
      float b = 1 - (effective_rotspeed * effective_rotspeed)/(diff.getRAD() * diff.getRAD());
      if(b <= 0) b = DBL_MIN;

      float lorentz_factor  = 1/sqrt(b);
      cur_rot_accel /= lorentz_factor;
    }

    effective_rotspeed += cur_rot_accel;

    if(rotate_side) {
      current_rotation.set(current_rotation.getDEG() + effective_rotspeed * DeltaTime * 2.5f, ANGLE_TYPE_DEG);
    } else {
      current_rotation.set(current_rotation.getDEG() - effective_rotspeed * DeltaTime * 2.5f, ANGLE_TYPE_DEG);
    }
  }
  
  
  //move forward  
  ship->setPosition(ship->getPosition() + core::vector3df(0.0,0.0,current_rotation.getDEG()).rotationToDirection(core::vector3df(0,speed * DeltaTime,0.0)));
  
  //rotate ship
  ship->setRotation(core::vector3df(90.0,0.0,rotation.getDEG()));
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

