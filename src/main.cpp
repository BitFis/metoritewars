#include <GL/glew.h> // Include the GLEW header file  
#include <GL/glut.h>
#include <GL/freeglut_ext.h> // Include the GLUT header file  


#include "game/scene/MenuScene.h"
#include "engine/Model_3DS.h"
#include "engine/Timer.h"


#include "game/Init.h"
#include "game/scene/GameScene.h"

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  

//temp texture
GLuint texture;

float angle = 0;

Model_3DS object;

void reshape (int width, int height) {  
  glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
  glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
  glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  

  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  

  glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}  
  
void keyPressed (unsigned char key, int x, int y) {  
  keyStates[key] = true; // Set the state of the current key to pressed  
  
  
  if (key == 27)  // If the left arrow key has been pressed // Perform left arrow key operations  
    glutExit();
  
}  
  
void keyUp (unsigned char key, int x, int y) {  
  keyStates[key] = false; // Set the state of the current key to not pressed  
}  


int main (int argc, char **argv) {  
  //temporary checking how long takes initialisation
  Timer timer;
  timer.reset();
  
  cout << "starting program at " << timer.getDouble() << endl;
  
  // do some initialization (glut & stuff)
  Init *init = new Init(&argc, argv);
  
  cout << "initialazing scenes at " << timer.getDouble() << endl;
          
  // create the world
  World *world = World::getInstance();
  
  cout << "created world at " << timer.getDouble() << endl;
  
  // create the scenes
  MenuScene *test = new MenuScene(world);
  cout << "created menuscene at " << timer.getDouble() << endl;
  
  GameScene *game = new GameScene(world);
  cout << "created gamescene at " << timer.getDouble() << endl;
  
  // add all the scenes to the world
  world->addScene(test);
  world->addScene(game);
  
  world->loadScene("menu");
  
  glutDisplayFunc (World::displayCallback);
  glutIdleFunc (World::displayCallback);
  glutReshapeFunc (reshape);
  glutKeyboardFunc(World::keyPressCallback);
  glutKeyboardUpFunc(World::keyUpCallback);
  glutMouseFunc(World::mouseCallback);
  
  cout << "starting loop at " << timer.getDouble() << endl;
    
  glutMainLoop ();
  
  world->removeScene(test);
  world->removeScene(game);
  
  delete test;
  delete game;
  delete init;
  
  return 0;
}  