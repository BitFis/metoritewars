
#include "TimerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TimerTest);

void TimerTest::setUp(){
  current_utc_time(&frameratecheck);
}

void TimerTest::tearDown(){
  
}

void TimerTest::testGetTimeDouble(){
  timespec tempframerate;
  double tempframerated;
  double framerate;
  
  current_utc_time(&tempframerate);
  
  timer.get(&framerate);
  
  frameratecheck.tv_nsec -= tempframerate.tv_nsec;
  frameratecheck.tv_sec -= tempframerate.tv_sec;
  
  //calc float
  tempframerated = (double)frameratecheck.tv_sec + (double)frameratecheck.tv_nsec / 1000000000;
  
  
//  printf("%lf | ", tempframerated);
//  printf("%lf\n", framerate);
  
  //check if it is a bit correct
  CPPUNIT_ASSERT(framerate <= tempframerated && framerate <= tempframerated);
}

void TimerTest::testGetTimeFloat(){
  
  timespec tempframerate;
  float tempframeratef;
  float framerate;
  
  current_utc_time(&tempframerate);
  
  frameratecheck.tv_nsec -= tempframerate.tv_nsec;
  frameratecheck.tv_sec -= tempframerate.tv_sec;
  
  timer.get(&framerate);
  
  //calc float
  tempframeratef = (float)frameratecheck.tv_sec + (float)frameratecheck.tv_nsec / 1000000000;
  
  //check if it is a bit correct
  CPPUNIT_ASSERT(framerate <= tempframeratef && framerate <= tempframeratef);
}

void TimerTest::testGetTime(){
  
  timespec tempframerate;
  timespec framerate;
  
  current_utc_time(&tempframerate);
  
  frameratecheck.tv_nsec -= tempframerate.tv_nsec;
  frameratecheck.tv_sec -= tempframerate.tv_sec;
  
  timer.get(&framerate);
  
  //check if it is a bit correct
  CPPUNIT_ASSERT(framerate.tv_sec == frameratecheck.tv_sec && framerate.tv_nsec <= frameratecheck.tv_nsec);
}

void TimerTest::testResetTimer(){
  double time1;
  double time2;
  
  timer.get(&time1);
  timer.reset();
  timer.get(&time2);
  
  CPPUNIT_ASSERT(time1 > time2);
}
