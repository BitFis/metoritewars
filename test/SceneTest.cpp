#include "SceneTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SceneTest);

void SceneTest::setUp() {
  world = new World();
  game_scene = new GameScene(world);
  menu_scene = new MenuScene(world);
  test_scene = new TestScene(world);
  
}

void SceneTest::tearDown() {
  delete game_scene;
  delete menu_scene;
  delete test_scene;
}

void SceneTest::testGetName() {
  CPPUNIT_ASSERT(game_scene->getName().compare("game") == 0);
  CPPUNIT_ASSERT(menu_scene->getName().compare("menu") == 0);
  CPPUNIT_ASSERT(test_scene->getName().compare("test") == 0);
}
