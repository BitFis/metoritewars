#include "MenuScene.h"

MenuScene::MenuScene(World *world) : Scene("menu", world) {

}

void MenuScene::onLoad() {
  std::cout << "menu scene load" << std::endl;
}

void MenuScene::onDraw() {
  std::cout << "menu scene draw" << std::endl;
}

void MenuScene::onUnload() {
  std::cout << "menu scene unload" << std::endl;
}
