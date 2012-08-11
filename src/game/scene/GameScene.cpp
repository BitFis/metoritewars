#include "GameScene.h"

using namespace std;

GameScene::GameScene(World *world) : Scene("game", world) {

}

void GameScene::onLoad(){
  
  testobj.Load("objects\\player\\ship.3ds");
  
  cout << "load gamescene" << endl;
  return;
}

void GameScene::onMouseEvent(int button, int state, int x, int y) {
  return;
}

void GameScene::onKeyPress(unsigned char key) {
  //27 = ESCAPE
  if(key == 27) {
    glutExit();
  }
  
  return;
}

void GameScene::onKeyUp(unsigned char key) {
  return;
}

void GameScene::onMove(){
  timer.reset();
  
  testobj.rot.y += 100 * timer.getfloat();
  return;
}

void GameScene::onDraw(){
  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  //glDisable(GL_LIGHTING);
  
  testobj.Draw();
  
  return;
}

void GameScene::onUnload(){
  return;
}

