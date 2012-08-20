#include "AngleTest.h"

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(AngleTest);

void AngleTest::setUp() {
}

void AngleTest::tearDown() {
}

void AngleTest::testConstruct() {
  Angle angle(0);
  Angle angle1(0, ANGLE_TYPE_RAD);
  Angle angle2(0, ANGLE_TYPE_DEG);
  Angle angle3(360.0f, ANGLE_TYPE_DEG);
  Angle angle4(0);
  angle4 = angle4 + (M_PI * 2);
  CPPUNIT_ASSERT(angle == angle1);
  CPPUNIT_ASSERT(angle2 == angle1);
  CPPUNIT_ASSERT(angle2 == angle);
  CPPUNIT_ASSERT(angle3 == angle);
  CPPUNIT_ASSERT(angle4 == angle);
  angle4 += (M_PI * 2);
  CPPUNIT_ASSERT(angle4 == angle);
}


void AngleTest::testSet() {
  Angle angle(0);
  float fangle = angle.getRAD();
  angle.set(1);
  CPPUNIT_ASSERT(fabs(angle.getRAD() - fangle) > 0.001);
  angle.set(1, ANGLE_TYPE_DEG);
  CPPUNIT_ASSERT(fabs(angle.getRAD() - fangle) > 0.001);
  
}

void AngleTest::testGetRAD() {

}

void AngleTest::testGetDEG() {

}
