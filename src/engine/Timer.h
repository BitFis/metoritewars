/* 
 * File:   Timer.h
 * Author: zurcherl
 *
 * 
 */

#ifndef TIMER_H
#define	TIMER_H

#include "time-helper.h"

class Timer {
public:
  Timer();
  void get(timespec* time);
  void get(double* time);
  void get(float* time);
  double getDouble();
  float getfloat();
  void reset();
  virtual ~Timer();
  
private:
  void calcDifTimer(timespec* time);
  
  timespec framespern;
  timespec currenttime;
  timespec lasttime;
};

#endif	/* TIMER_H */

