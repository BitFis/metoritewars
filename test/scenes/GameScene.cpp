#include "GameScene.h"

#include <iostream>

using namespace std;

GameScene::GameScene(World *world) : Scene("game", world) {
}

void GameScene::onLoad() {
  return;
}

bool GameScene::OnEvent(const SEvent& event) {
  return false;
}

void GameScene::onTick() {
  return;
}

void GameScene::onUnload() {
  return;
}
