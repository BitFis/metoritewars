#include "game-scene.h"

GameScene::GameScene(World *world) : Scene("game", world) {

}

void GameScene::on_load() {
  cout << "game scene load" << endl;
}

void GameScene::on_draw() {
  cout << "game scene draw" << endl;
}

void GameScene::on_unload() {
  cout << "game scene unload" << endl;
}
