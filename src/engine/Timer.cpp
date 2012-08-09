/* 
 * File:   Timer.cpp
 * Author: zurcherl
 * 
 * Created on 8. August 2012, 16:58
 */

#include "Timer.h"

Timer::Timer() {
  reset();
}

void Timer::get(timespec* time){
  *time = framespern;
}

void Timer::calcDifTimer(timespec* time){
  
  //calc difference of time
  time->tv_nsec = currenttime.tv_nsec -  lasttime.tv_nsec;
  time->tv_sec = currenttime.tv_sec - lasttime.tv_sec;
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

