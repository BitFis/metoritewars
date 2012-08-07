#include "GameScene.h"

GameScene::GameScene(World *world) : Scene("game", world) {

}

void GameScene::onLoad() {
  cout << "game scene load" << endl;
}

void GameScene::onDraw() {
  cout << "game scene draw" << endl;
}

void GameScene::onUnload() {
  cout << "game scene unload" << endl;
}
