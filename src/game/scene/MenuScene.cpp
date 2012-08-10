#include "MenuScene.h"

MenuScene::MenuScene(World *world) : Scene("menu", world) {

}

void MenuScene::onLoad() {
  std::cout << "menu scene load" << std::endl;
}

void MenuScene::onMove() {
  std::cout << "menu scene move" << std::endl;
  world->loadScene("game");
}

void MenuScene::onDraw() {
  std::cout << "menu scene draw" << std::endl;
}

void MenuScene::onUnload() {
  std::cout << "menu scene unload" << std::endl;
}
