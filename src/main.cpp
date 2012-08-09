#include <GL/glew.h> // Include the GLEW header file  
#include <GL/glut.h>
#include <GL/freeglut_ext.h> // Include the GLUT header file  

#include "engine/Object.h"
#include "engine/Model_3DS.h"
#include "engine/GLTexture.h"

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  

//temp texture
GLuint texture;

float angle = 0;

Model_3DS object;
  
void keyOperations (void) {  
  
}
  
void display (void) {  
  glClearColor (0.0,0.0,0.0,1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();  
  gluLookAt (0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 

  glDisable(GL_TEXTURE_2D);

  object.rot.x = 90;
  
  object.Draw();
  
  angle += 0.2;
  
  glutSwapBuffers();
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
  
void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

int main (int argc, char **argv) {  
  
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    
    
    init ();
    
    
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    
    
    //cout << texture << endl;
    
    object.Load("C:\\metoritewars\\objects\\player\\ship.3ds");
    
    glutMainLoop ();

    //Free our texture
    //FreeTexture( texture );

    return 0;
  /**
  texture = obj.loadBmpTexture("C:\\metoritewars\\objects\\player\\road.bmp");
  
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    
    glutMainLoop ();
    return 0; */
}  