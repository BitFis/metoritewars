#include "MenuScene.h"

MenuScene::MenuScene(World *world) : Scene("menu", world) {
}

void MenuScene::onLoad() {
  return;
}

bool MenuScene::OnEvent(const SEvent& event) {
  return false;
}

void MenuScene::onTick() {
  return;
}

void MenuScene::onUnload() {
  return;
}
