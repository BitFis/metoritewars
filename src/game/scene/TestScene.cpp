/* 
 * File:   TestScene.cpp
 * Author: zurcherl
 * 
 * Created on 9. August 2012, 16:25
 */

#include "TestScene.h"

TestScene::TestScene(World *world) : Scene("test", world){
  counter = 0;
}

void TestScene::onLoad(){
  testobj.Load("C:\\metoritewars\\objects\\player\\ship.3ds");
  return;
}

void TestScene::onMove(){
  
  time.reset();
  cout << time.getDouble() << endl;
  testobj.rot.x += 10 * time.getDouble();
  
  glTranslatef(0.0,0.0,-10.0);
  glRotated(90,1.0,0.0,0.0);
  return;
}

void TestScene::onDraw(){
  
  //cout << time.getDouble() << endl;
  
  testobj.Draw();
  return;
}

void TestScene::onUnload(){
  return;
}

