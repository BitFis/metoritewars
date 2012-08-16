#include "TestScene.h"
#include <iostream>

using namespace std;

TestScene::TestScene(World *world) : Scene("test", world) {
  on_load_called = false;
  on_unload_called = false;
}

void TestScene::onLoad() {
  on_load_called = true;
  return;
}

bool TestScene::OnEvent(const SEvent& event) {
  return false;
}

void TestScene::onTick() {
  return;
}

void TestScene::onUnload() {
  on_unload_called = true;
  return;
}
