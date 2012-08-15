#include "TestScene.h"
#include <iostream>

using namespace std;

TestScene::TestScene(World *world) : Scene("test", world) {
}

void TestScene::onLoad() {
  return;
}

bool TestScene::OnEvent(const SEvent& event) {
  return false;
}

void TestScene::onTick() {
  return;
}

void TestScene::onUnload() {
  return;
}
