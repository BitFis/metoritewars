/* 
 * File:   TimerTest.h
 * Author: zurcherl
 *
 * Created on 9. August 2012, 09:06
 */

#ifndef TIMERTEST_H
#define	TIMERTEST_H

#include "../src/engine/time-helper.h"

#include "../src/engine/Timer.h"
#include <cppunit/extensions/HelperMacros.h>
#include <stdexcept>

class TimerTest : public CppUnit::TestFixture {
private:
  CPPUNIT_TEST_SUITE(TimerTest);
  CPPUNIT_TEST(testGetTime);
  CPPUNIT_TEST(testGetTimeFloat);
  CPPUNIT_TEST(testGetTimeDouble);
  CPPUNIT_TEST_SUITE_END();
  
  Timer timer;
  timespec frameratecheck;
  
public:
  void setUp();
  void tearDown();
  
  void testGetTimeDouble();
  void testGetTimeFloat();
  void testGetTime();
  
  void testResetTimer();
};

#endif	/* TIMERTEST_H */

