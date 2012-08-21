#include "GameScene.h"

GameScene::GameScene(World *world) : Scene("game", world){
  
};

void GameScene::onLoad(){
  ship = new Ship("objects/player/ship.x", this->smgr, this->driver);
  this->meteors = new vector<Meteor*>(0);
  
  camera = smgr->addCameraSceneNode(0,core::vector3df(0.0,0.0,2.0),core::vector3df(0.0,0.0,0.0),1,true);
  
  last_meteor_created_at = device->getTimer()->getTime();
  
  gui->getSkin()->setColor(gui::EGDC_BUTTON_TEXT,video::SColor(255, 255, 255, 255));
  gui->getSkin()->setSize(gui::EGDS_BUTTON_HEIGHT, 500);
  
  //reset to normal font
  gui->getSkin()->setFont(gui->getBuiltInFont(), gui::EGDF_DEFAULT);
  
  gui->addStaticText(L"POINTS: 0", core::rect<s32>(20,20,350,40), false);
  
  //background
  background = new Background(smgr, driver);
}

bool GameScene::OnEvent(const SEvent& event){
  
  return false;
}

void GameScene::onTick(){
  
  background->returnStars()->setPosition(ship->getShipNode()->getPosition() + core::vector3df(2.5,-6.0,0.0));
  
  //update ship
  core::vector3df pos;
  ship->update(world->getFrameDeltaTime());
  pos = ship->getPosVec3df();
  pos.Z = camera->getPosition().Z;
  
  camera->setPosition(pos);
  camera->setTarget(ship->getPosVec3df());
  
  Meteor::setSpawnOffset(ship->getPosVec3df());
  
  
  /////////////////////////////////////////
  //shoot
  
  if(world->getKeys()->get(KEY_SPACE)){
    ship->shoot(world->getRunTime());
  }
  
  ////////////////////////////////////////
  //move ship forward
  if(world->getKeys()->get(KEY_UP)){
    ship->moveFor();
  }
  
  //move ship back
  if(world->getKeys()->get(KEY_DOWN)){
    ship->moveBack();
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
  
  vector<scene::ISceneNode*>::iterator shot_last_it;
  vector<scene::ISceneNode*> &shots = ship->getShots()->getShotNode();
  /* check for collisions between meteors */
  foreach(it_meteor1, (*this->meteors)) {
    foreach(it_meteor2, (*this->meteors)) {
      if(*it_meteor1 != *it_meteor2) {
        if((*it_meteor1)->collidesWith((*it_meteor2))) {
          (*it_meteor1)->bounceOf(*it_meteor2);
        }
      }
    }
    
    shot_last_it = shots.begin();
    //check if it collided with a shot of the ship
    foreach(shot, shots){
      
      //remove shot if it is outside of the ring
      if(tooFarAwayFrom((*shot), ship->getPosVec3df(), 2.3f)){
        ship->getShots()->removeShot(shot);
        shot = shot_last_it;
      }else if((*it_meteor1)->collidesWith((*shot), 1.0)){
        //removing shot if it hit a meteor
        ship->getShots()->removeShot(shot);
        shot = shot_last_it;
        (*it_meteor1)->getMesh()->setPosition(ship->getPosVec3df()+core::vector3df(100.0,100.0,100.0));
      } else {
        shot_last_it = shot;
      }
    }
    
    //check if it collided with the ship
    if((*it_meteor1)->collidesWith((ship->getShipNode()), 1.0)){
      std::cout << "you killed your self!!" << endl;
      //take lives from the ship
    }
  }
  
  /* remove old meteors */
  Meteor *meteor;
  vector<Meteor*>::iterator last_it = this->meteors->begin();
  foreach(it_meteor, (*this->meteors)) {
    meteor = *it_meteor;
    if(tooFarAwayFrom(meteor->getMesh(), ship->getPosVec3df(), 2.3f)) {
      this->meteors->erase(it_meteor);
      smgr->addToDeletionQueue(meteor->getMesh());
      it_meteor = last_it;
    } else {
      last_it = it_meteor;
      meteor->update(world->getFrameDeltaTime());
    }
  }
}

void GameScene::onUnload(){
  delete background;
  delete ship;
  foreach(meteor, (*this->meteors)) {
    delete *meteor;
  }
  delete meteors;
}

bool GameScene::tooFarAwayFrom(scene::IAnimatedMeshSceneNode* mesh, core::vector3df pos, float distance) {
  return fabs(distance) < fabs(mesh->getPosition().getDistanceFrom(pos));
}

bool GameScene::tooFarAwayFrom(scene::ISceneNode* mesh, core::vector3df pos, float distance) {
  return fabs(distance) < fabs(mesh->getPosition().getDistanceFrom(pos));
}

