#ifndef SCENETEST_H
#define	SCENETEST_H

#include "../src/Scene.h"
#include "scenes/GameScene.h"
#include "scenes/MenuScene.h"
#include "scenes/TestScene.h"
#include <cppunit/extensions/HelperMacros.h>

class SceneTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(SceneTest);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST_SUITE_END();
    
    GameScene *game_scene;
    MenuScene *menu_scene;
    TestScene *test_scene;
    World *world;
    
  public:
    void setUp();
    void tearDown();
    
    void testGetName();
};

#endif	/* SCENETEST_H */

