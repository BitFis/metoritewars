/* 
 * File:   Timer.cpp
 * Author: zurcherl
 * 
 * Created on 8. August 2012, 16:58
 */

#include "Timer.h"

#include <iostream>
using namespace std;

Timer::Timer() {
  reset();
}

void Timer::get(timespec* time){
  *time = framespern;
}

void Timer::calcDifTimer(timespec* time){
  
  // calculate the diffrence of the nanoseconds
  long nano = (currenttime.tv_nsec - lasttime.tv_nsec);
  int add = 0;

  // some calculations if the nanoseconds of struct 1 were bigger
  if(nano < 0) {
    nano = 1000000000 + nano;
    add = 1;
  }
  time->tv_nsec = nano;
  // add the seconds
  time->tv_sec = (currenttime.tv_sec - lasttime.tv_sec - add);
}

void Timer::get(double* time){
  
  *time = (double)framespern.tv_nsec / 1000000000;
  *time += (double)framespern.tv_sec;
  
  return;
}

double Timer::getDouble(){
  double temptime;
  get(&temptime);
  
  
  return temptime;
  
  //return timeval_diff(&lasttime, &currenttime);
}
  
float Timer::getfloat(){
  float temptime;
  get(&temptime);
  return temptime;
}

void Timer::get(float* time){
  
  double temptime;
  
  get(&temptime);
  
  //always in seconds
  *time = (float)temptime;
  
  return;
}

void Timer::reset(){
  //get last time
  lasttime = currenttime;
  
  //get current time
  current_utc_time(&currenttime);
  //get diffrence between the times
  calcDifTimer(&framespern);
}

Timer::~Timer() {
  
}

