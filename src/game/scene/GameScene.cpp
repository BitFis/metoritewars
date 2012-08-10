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
  
  glRotatef(45,1.0,0.0,0.0);
  
  //glTranslatef(0.0,0.0,-20.0);
  
  glBegin(GL_TRIANGLES);					
		glColor3f(0.0f,0.0f,1.0f);			
		glVertex3f( 0.0f, 1.0f, 0.0f);		
		glColor3f(0.0f,1.0f,0.0f);			
		glVertex3f(-1.0f,-1.0f, 0.0f);		
		glColor3f(1.0f,0.0f,0.0f);			
		glVertex3f( 1.0f,-1.0f, 0.0f);		
	glEnd();
 
  
  testobj.Draw();
  
  return;
}

void GameScene::onUnload(){
  return;
}

