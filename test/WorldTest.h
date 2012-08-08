#ifndef WORLDTEST_H
#define	WORLDTEST_H

#include "../src/World.h"
#include "scenes/GameScene.h"
#include <cppunit/extensions/HelperMacros.h>

class WorldTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(WorldTest);
    CPPUNIT_TEST(testContructor);
    CPPUNIT_TEST(testGetScene);
    CPPUNIT_TEST(testGetCurrentScene);
    CPPUNIT_TEST(testAddScene);
    CPPUNIT_TEST(testRemoveScene);
    CPPUNIT_TEST(testLoadScene);
    CPPUNIT_TEST(testUnloadScene);
    CPPUNIT_TEST_SUITE_END();
    
    GameScene *game_scene;
    World *world;
    
  public:
    void setUp();
    void tearDown();
    
    void testContructor();
    void testGetScene();
    void testGetCurrentScene();
    void testAddScene();
    void testRemoveScene();
    void testLoadScene();
    void testUnloadScene();
};

#endif	/* WORLDTEST_H */

