#include "SceneTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SceneTest);

void SceneTest::setUp() {
  world = new World();
  scene = new GameScene(world);
  
}

void SceneTest::tearDown() {
  delete scene;
}

void SceneTest::testGetName() {
  CPPUNIT_ASSERT(scene->getName().compare("game") == 0);
}

