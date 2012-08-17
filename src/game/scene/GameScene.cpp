#include "GameScene.h"

GameScene::GameScene(World *world) : Scene("game", world){
  
};

void GameScene::onLoad(){
  ship = new Ship("objects/player/ship.x", this->smgr);
  this->meteors = new vector<Meteor*>(0);
  
  last_meteor_created_at = device->getTimer()->getTime();
}

bool GameScene::OnEvent(const SEvent& event){
  
  return false;
}

void GameScene::onTick(){
  //update ship
  ship->update(world->getFramDeltaTime());
  
  ////////////////////////////////////////
  //move ship forward
  if(world->getKeys()->get(KEY_UP)){
    ship->moveFor(world->getFramDeltaTime());
  }
  
  //move ship back
  if(world->getKeys()->get(KEY_DOWN)){
    ship->moveBack(world->getFramDeltaTime());
  }
  
  //rotate ship
  if(world->getKeys()->get(KEY_RIGHT)){
    ship->rotate(1, world->getFramDeltaTime());
  }
  
  if(world->getKeys()->get(KEY_LEFT)){
    ship->rotate(-1, world->getFramDeltaTime());
  
  /* spawn new meteor every 500 ms*/
  unsigned int tick = device->getTimer()->getTime();
  int count = (tick - last_meteor_created_at) / 500;
  if(count) {
    last_meteor_created_at = tick;
    for(int i = 0; i < count; i++) {
      this->meteors->push_back(new Meteor(smgr));
    }
  }
  
  /* remove old meteors */
  foreach(it_meteor, (*this->meteors)) {
    if((*it_meteor)->animationFinished()) {
      smgr->addToDeletionQueue((*it_meteor)->getMesh());
      this->meteors->erase(it_meteor);
    }
  }
  
  /* check for collisions between meteors */
  foreach(it_meteor1, (*this->meteors)) {
    foreach(it_meteor2, (*this->meteors)) {
      if(*it_meteor1 != *it_meteor2) {
        if((*it_meteor1)->collidesWith((*it_meteor2)->getMesh())) {
          
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

