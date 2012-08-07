#ifndef SCENETEST_H
#define	SCENETEST_H

#include "../src/Scene.h"
#include "scenes/GameScene.h"
#include <cppunit/extensions/HelperMacros.h>

class SceneTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(SceneTest);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST_SUITE_END();
    
    GameScene *scene;
    World *world;
    
  public:
    void setUp();
    void tearDown();
    
    void testGetName();
};

#endif	/* SCENETEST_H */

