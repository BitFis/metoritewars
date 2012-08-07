#include <GL/glew.h> // Include the GLEW header file  
#include <GL/glut.h>
#include <GL/freeglut_ext.h> // Include the GLUT header file  

#include "Object.h"

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  

Object obj ("C:\\metoritewars\\objects\\player\\test.obj");
  
void keyOperations (void) {  
  
}
  
void display (void) {  
  keyOperations();  

  glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red  
  glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
  glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  

  glTranslatef(0.0f, 0.0f, -5.0f); // Push eveything 5 units back into the scene, otherwise we won't see the primitive  

  glTranslatef(0.0f, 0.0, 0.0f); // Translate our object along the y axis  

  glRotatef(45, 0.0f, 1.0f, 0.0f); // Rotate our object around the y axis  

  glutWireCube(2.0f); // Render the primitive  
  
  glFlush();
}  
  
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
  glutInit(&argc, argv); // Initialize GLUT  
  glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)  
  glutInitWindowSize (500, 500); // Set the width and height of the window  
  glutInitWindowPosition (100, 100); // Set the position of the window  
  glutCreateWindow ("You're first OpenGL Window"); // Set the title for the window  

  glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  

  glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  

  glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
  glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events 

  glutMainLoop(); // Enter GLUT's main loop  
}  