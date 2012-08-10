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
  return;
}

void GameScene::onKeyUp(unsigned char key) {
  return;
}

void GameScene::onMove(){
  timer.reset();
  
  testobj.rot.x += 100 * timer.getDouble();
  testobj.rot.y += 100 * timer.getDouble();;
  
  return;
}

void GameScene::onDraw(){
  
  glTranslatef(0.0,0.0,-10.0);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  
  glEnable(GL_TEXTURE_2D);
  
  testobj.Materials->tex.Use();
  
	glBegin(GL_TRIANGLES);					
		glColor4f(0.0f,0.0f,1.0f, 1.0f);		
		glColor4f(0.0f,1.0f,0.0f, 0.5f);	
		glColor4f(1.0f,0.0f,0.0f, 0.7f);	
	glEnd();
  
  //gluLookAt(0.0,0.0,0.0,0.0,0.0,-5.0,0.0,0.0,0.0);
  testobj.Draw();
  return;
}

void GameScene::onUnload(){
  return;
}

