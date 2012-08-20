#include "GameScene.h"

GameScene::GameScene(World *world) : Scene("game", world){
  
};

void GameScene::onLoad(){
  ship = new Ship("objects/player/ship.x", this->smgr);
  this->meteors = new vector<Meteor*>(0);
  
  scene::ICameraSceneNode* camera = smgr->addCameraSceneNode(0,core::vector3df(0.0,0.0,2.0),core::vector3df(0.0,0.0,0.0),1,true);
  
  last_meteor_created_at = device->getTimer()->getTime();
}

bool GameScene::OnEvent(const SEvent& event){
  
  return false;
}

void GameScene::onTick(){
  //update ship
  ship->update(world->getFrameDeltaTime());
  
  /////////////////////////////////////////
  //shoot
  
  if(world->getKeys()->get(KEY_SPACE)){
    ship->shoot(world->getRunTime());
  }
  
  ////////////////////////////////////////
  //move ship forward
  if(world->getKeys()->get(KEY_UP)){
    ship->moveFor(world->getFrameDeltaTime());
  }
  
  //move ship back
  if(world->getKeys()->get(KEY_DOWN)){
    ship->moveBack(world->getFrameDeltaTime());
  }
  
  //rotate ship
  if(world->getKeys()->get(KEY_RIGHT)){
    ship->rotate(-1, world->getFrameDeltaTime());
  }
  
  if(world->getKeys()->get(KEY_LEFT)){
    ship->rotate(1, world->getFrameDeltaTime());
  }
  
  /* spawn new meteor every 500 ms*/
  unsigned int tick = device->getTimer()->getTime();
  int count = (tick - last_meteor_created_at) / 100;
  if(count) {
    last_meteor_created_at = tick;
    for(int i = 0; i < count; i++) {
      this->meteors->push_back(new Meteor(smgr));
    }
  }
  
  /* remove old meteors */
  Meteor *meteor;
  vector<Meteor*>::iterator last_it = this->meteors->begin();
  foreach(it_meteor, (*this->meteors)) {
    meteor = *it_meteor;
    if(meteor->tooFarAwayFrom(core::vector3df(0,0,0), 2.3f)) {
      this->meteors->erase(it_meteor);
      smgr->addToDeletionQueue(meteor->getMesh());
      it_meteor = last_it;
    } else {
      last_it = it_meteor;
      meteor->update(world->getFrameDeltaTime());
    }
  }
  
  /* check for collisions between meteors */
  foreach(it_meteor1, (*this->meteors)) {
    foreach(it_meteor2, (*this->meteors)) {
      if(*it_meteor1 != *it_meteor2) {
        if((*it_meteor1)->collidesWith((*it_meteor2))) {
          (*it_meteor1)->bounceOf(*it_meteor2);
        }
      }
    }
  }
}

void GameScene::onUnload(){
  delete ship;
  foreach(meteor, (*this->meteors)) {
    delete *meteor;
  }
  delete meteors;
}

