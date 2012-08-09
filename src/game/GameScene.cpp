/* 
 * File:   GameScene.cpp
 * Author: zurcherl
 * 
 * Created on 9. August 2012, 15:53
 */

#include "GameScene.h"

using namespace std;

GameScene::GameScene(World *world) : Scene("game", world) {

}

void GameScene::onLoad(){
  
  testobj.Load("C:\\metoritewars\\objects\\player\\ship.3ds");
  cout << "load gamescene" << endl;
  return;
}

void GameScene::onMove(){
  //testobj.rot.z += 2;
  return;
}

void GameScene::onDraw(){
  
  glTranslatef(0.0,0.0,-10.0);
  
  //glutSolidCube(2);
  
  //gluLookAt(0.0,0.0,0.0,0.0,0.0,-5.0,0.0,0.0,0.0);
  testobj.Draw();
  return;
}

void GameScene::onUnload(){
  return;
}

