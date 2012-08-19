#ifndef ANGLETEST_H
#define	ANGLETEST_H

#include "../src/engine/Angle.h"
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
using namespace std;

class AngleTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(AngleTest);
    CPPUNIT_TEST(testConstruct);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST(testGetRAD);
    CPPUNIT_TEST(testGetDEG);
    CPPUNIT_TEST_SUITE_END();
    
  public:
    void setUp();
    void tearDown();
    
    void testConstruct();
    void testSet();
    void testGetRAD();
    void testGetDEG();
};

#endif	/* ANGLETEST_H */

