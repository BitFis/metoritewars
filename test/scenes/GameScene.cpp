#include "GameScene.h"

#include <iostream>

using namespace std;

GameScene::GameScene(World *world) : Scene("game", world) {
}

void GameScene::onLoad() {
  cout << "game scene on load" << endl;
}

void GameScene::onDraw() {
}

void GameScene::onUnload() {
  cout << "void" << endl;
}
