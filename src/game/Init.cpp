#include "Init.h"

Init::Init(int *argc, char **argv) {
  /* your GL initialization code */
  
  glutInit (argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize (500, 500);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("A basic OpenGL Window");
  glutFullScreen();
  
  glMatrixMode(GL_MODELVIEW);
  
  // some lightning
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
}

Init::~Init() {
  /* some cleanup maybe? */
}

