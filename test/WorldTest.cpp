#include "WorldTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(WorldTest);

void WorldTest::setUp() {
  world = new World();
  game_scene = new GameScene(world);
  menu_scene = new MenuScene(world);
  test_scene = new TestScene(world);
  world->addScene(game_scene);
  world->addScene(menu_scene);
  world->addScene(test_scene);
}

void WorldTest::tearDown() {
  delete game_scene;
  delete menu_scene;
  delete test_scene;
  delete world;
}

void WorldTest::testGetScene() {
  CPPUNIT_ASSERT(world->getScene("game") == game_scene);
  CPPUNIT_ASSERT(world->getScene("menu") == menu_scene);
  CPPUNIT_ASSERT(world->getScene("test") == test_scene);
  
  // throws an invalid_argument exception
  CPPUNIT_ASSERT_THROW(world->getScene("random inexistent scene"), invalid_argument);
}

void WorldTest::testGetCurrentScene() {
  // throws an out_of_range exception
  CPPUNIT_ASSERT_THROW(world->getCurrentScene(), out_of_range);
  world->loadScene("game");
  CPPUNIT_ASSERT(game_scene == world->getCurrentScene());
}

void WorldTest::testAddScene() {
  // should throw an exception because it has already been added on construction
  CPPUNIT_ASSERT_THROW(world->addScene(game_scene), invalid_argument);
}

void WorldTest::testRemoveScene() {
  CPPUNIT_FAIL("not yet implemented");
}

void WorldTest::testLoadScene() {
  CPPUNIT_FAIL("not yet implemented");
}

void WorldTest::testUnloadScene() {
  CPPUNIT_FAIL("not yet implemented");
}

