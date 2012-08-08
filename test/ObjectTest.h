#ifndef OBJECTTEST_H
#define	OBJECTTEST_H

#include "../src/engine/Object.h"
#include <cppunit/extensions/HelperMacros.h>

class ObjectTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(ObjectTest);
    CPPUNIT_TEST(testLoadObject);
    CPPUNIT_TEST(testCalculateNormals);
    CPPUNIT_TEST_SUITE_END();
    
    Object *obj;
  public:
    void setUp();
    void tearDown();
    
    void testLoadObject();
    void testCalculateNormals();
};

#endif	/* OBJECTTEST_H */

