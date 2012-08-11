#include "MenuScene.h"
#include "GameScene.h"

MenuScene::MenuScene(World *world) : Scene("menu", world) {

}

void MenuScene::onLoad() {
  
  //load welcomes GUI
  menugui = SOIL_load_OGL_texture
	(
		"objects/menu/menu.png",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA
	);
  
  //load background img
  background = SOIL_load_OGL_texture
	(
		"objects/menu/menubg.png",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_TEXTURE_REPEATS
	);
  
  planet.Load("objects/planet/planet.3ds");
  ship.Load("objects/player/ship.3ds");
  
  moon.copyMesh(planet);
  
  planet.pos.x = -4;
  planet.pos.y = -3;
  planet.scale = 1.5;
  
  std::cout << "menu scene load" << std::endl;
}

void MenuScene::onMouseEvent(int button, int state, int x, int y) {
  return;
}

void MenuScene::onKeyPress(unsigned char key) {
  //27 = ESCAPE
  if(key == 27) {
    glutExit();
  }
  
  if(key == 13)
    world->loadScene("game");
  
  return;
}

void MenuScene::onKeyUp(unsigned char key) {
  return;
}
void MenuScene::onMove() {
  timer.reset();
          
  //rotate planet
  planet.rot.y += timer.getDouble() * 5;
}

void MenuScene::onDraw() {
  
  /////////////////////////////
  //draw background
	glPushMatrix();
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,background);
  
  //disable light for background
  glDisable(GL_LIGHTING);
  
  //move GUI to front
  glTranslatef(0.0,0.0,-89.0);
  glScalef(100,100,100);
  
  glBegin( GL_QUADS );
  glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0);
  glTexCoord2d(3.0,0.0); glVertex2d(1.0,-1.0);
  glTexCoord2d(3.0,3.0); glVertex2d(1.0,1.0);
  glTexCoord2d(0.0,3.0); glVertex2d(-1.0,1.0);
  glEnd();
  
  //enable light after drawing background
  glEnable(GL_LIGHTING);
  
  glPopMatrix();
  //////////////////////////////////7
  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  
  planet.Draw();
  moon.Draw();
  
  /////////////////////////////////
  //draw GUI
	glPushMatrix();
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,menugui);
  
  //move GUI to front
  glTranslatef(0.0,0.0,9.0);
  glScalef(0.4,0.2,0.2);
  
  glBegin( GL_QUADS );
  glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0);
  glTexCoord2d(1.0,0.0); glVertex2d(1.0,-1.0);
  glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
  glTexCoord2d(0.0,1.0); glVertex2d(-1.0,1.0);
  glEnd();
  
  glPopMatrix();
  /////////////////////////////
}

void MenuScene::onUnload() {
  std::cout << "menu scene unload" << std::endl;
}
