/* 
 * File:   Timer.cpp
 * Author: zurcherl
 * 
 * Created on 8. August 2012, 16:58
 */

#include "Timer.h"

Timer::Timer() {
  current_utc_time(&currenttime);
  lasttime = currenttime;
}

Timer::Timer(const Timer& orig) {
}

void Timer::get(timespec* time){
  this->update();
  
  calcDifTimer(time);
}

void Timer::calcDifTimer(timespec* time){
  this->update();
  
  //calc difference of time
  time->tv_nsec = lasttime.tv_nsec - currenttime.tv_nsec;
  time->tv_sec = lasttime.tv_sec - currenttime.tv_sec;
}

void Timer::get(double* time){
  this->update();
  
  *time = (double)this->currenttime.tv_nsec / 1000000000;
  *time += (double)this->currenttime.tv_sec;
  
  return;
}

void Timer::get(float* time){
  this->update();
  
  //always in seconds
  *time = (float)this->currenttime.tv_nsec / 1000000000;
  *time += (float)this->currenttime.tv_sec;
  
  return;
}

void Timer::update(){
  current_utc_time(&currenttime);
}

void Timer::reset(){
  current_utc_time(&currenttime);
  
  //reset last timecheck
  lasttime.tv_nsec = currenttime.tv_nsec;
  lasttime.tv_sec = currenttime.tv_sec;
}

Timer::~Timer() {
  
}

