#include "GameScene.h"

GameScene::GameScene(World *world) : Scene("game", world){
  
};

void GameScene::onLoad(){
  ship = new Ship("objects/player/ship.3ds", this->smgr);
  meteor = new Meteor(smgr);
}

bool GameScene::OnEvent(const SEvent& event){
  return false;
}

void GameScene::onTick(){
  
}

void GameScene::onUnload(){
  delete ship;
  delete meteor;
}

