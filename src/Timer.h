/* 
 * File:   Timer.h
 * Author: zurcherl
 *
 * Created on 8. August 2012, 16:58
 */

#ifndef TIMER_H
#define	TIMER_H

#include "engine/time-helper.h"


class Timer {
public:
  Timer();
  Timer(const Timer& orig);
  timespec get();
  timespec set();
  double get();
  double set();
  virtual ~Timer();
private:

};

#endif	/* TIMER_H */

