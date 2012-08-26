#include "Ship.h"

Ship::Ship(const char*  filename, scene::ISceneManager* smgr, video::IVideoDriver* driver) {
  lastshot = 0;
  ship = smgr->addAnimatedMeshSceneNode(smgr->getMesh(filename),0,12,core::vector3df(0.0,0.0,0.0),core::vector3df(0.0,180.0,0.0),core::vector3df(0.01,0.01,0.01),smgr);
  
  this->driver = driver;
  this->smgr = smgr;
  
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
    ship->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
    //ship->getMaterial(0).SpecularColor.set(0,0,0,0);
    //ship->setMaterialFlag(video::EMF_LIGHTING, true);
    //ship->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  }
  
  //set Animations
  ship->setFrameLoop(0,39);
  ship->setAnimationSpeed(10);
  
    
  
  shipfire = smgr->addParticleSystemSceneNode(false, ship, 1337);
  scene::IParticleEmitter* emitter = shipfire->createBoxEmitter(
          core::aabbox3d<f32>(-1.1,1.1,-1.1,0.0,0.1,0.1), // emitter size
          core::vector3df(0.0f,0.0f,0.0f),          // initial direction
          200,1000,                                 // emit rate
          video::SColor(0,255,255,255),             // darkest color
          video::SColor(0,255,255,255),             // brightest color
          200,250,0,                              // min and max age, angle
          core::dimension2df(0.0f,0.0f),            // min size
          core::dimension2df(0.02f,0.02f));
  
  shipfire->setEmitter(emitter);
  
  scene::IParticleAffector* paf = shipfire->createFadeOutParticleAffector();
  
  shipfire->addAffector(paf);
  
  paf->drop();

  shipfire->setRotation(core::vector3df(0.0,0.0,0.0));
  shipfire->setScale(core::vector3df(2.0,2.0,2.0));
  shipfire->setPosition(core::vector3df(1.1f,-2.0f,3.0f));
  shipfire->setMaterialFlag(video::EMF_LIGHTING, false);
  shipfire->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
  shipfire->setMaterialTexture(0, driver->getTexture("objects/player/ship-effect.png"));
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
  float cur_accel = 0.0f;
  
  
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
    float reverse = (speed < 0) ? 3 : 1;
    float b = 1 - (speed * speed)/((max_speed / reverse) * (max_speed / reverse));
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

    current_rotation.set(current_rotation.getDEG() - effective_rotspeed * DeltaTime * 2.5f, ANGLE_TYPE_DEG);
    
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
  Angle diff(current_rotation - rotation);
  diff = diff > M_PI ? diff + (M_PI / 2.0f) : diff;
  if(diff < (M_PI / 2.0f)) {
    rotation.set(rotation.getDEG() - rotspeed * rotate * deltaTime, ANGLE_TYPE_DEG);
  }
}

Angle Ship::getRotation() {
  return this->current_rotation;
}

Shot* Ship::getShots() {
  return shots;
}

Ship::~Ship() {
  delete shots;
}

