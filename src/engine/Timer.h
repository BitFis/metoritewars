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
  Timer(const Timer& orig);
  void get(timespec* time);
  void get(double* time);
  void get(float* time);
  void reset();
  void update();
  virtual ~Timer();
  
private:
  void calcDifTimer(timespec* time);
  
  timespec currenttime;
  timespec lasttime;
};

#endif	/* TIMER_H */

