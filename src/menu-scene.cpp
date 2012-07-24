#include "menu-scene.h"

MenuScene::MenuScene(World *world) : Scene("menu", world) {

}

void MenuScene::on_load() {
  std::cout << "menu scene load" << std::endl;
}

void MenuScene::on_draw() {
  std::cout << "menu scene draw" << std::endl;
}

void MenuScene::on_unload() {
  std::cout << "menu scene unload" << std::endl;
}
