#include "GameScene.h"

GameScene::GameScene(World *world) : Scene("game", world){
  
};

void GameScene::onLoad(){
  ship = new Ship("objects/player/ship.3ds", this->smgr);
  this->meteors = new vector<Meteor*>(0);
  for(int i = 0; i < 20; i++) {
    this->meteors->push_back(new Meteor(smgr));
  }
}

bool GameScene::OnEvent(const SEvent& event){
  return false;
}

void GameScene::onTick(){
  cout << "asdasd" << endl;
}

void GameScene::onUnload(){
  delete ship;
  foreach(meteor, (*this->meteors)) {
    delete *meteor;
  }
  delete meteors;
}

