/* 
 * File:   TestScene.cpp
 * Author: zurcherl
 * 
 * Created on 9. August 2012, 16:25
 */

#include "TestScene.h"

TestScene::TestScene(World *world) : Scene("test", world){
  
}

void TestScene::onLoad(){
  testobj.Load("C:\\metoritewars\\objects\\player\\ship.3ds");
  return;
}

void TestScene::onMove(){
  time.reset();
  
  time.get(&timer);
  
  testobj.rot.x += 10000 * timer;
  
  glTranslatef(0.0,0.0,-10.0);
  glRotated(90,1.0,0.0,0.0);
  return;
}

void TestScene::onDraw(){
  
  cout << timer << endl;
  
  testobj.Draw();
  return;
}

void TestScene::onUnload(){
  return;
}

