#include <GL/glew.h> // Include the GLEW header file  
#include <GL/glut.h> // Include the GLUT header file  
#include "Model_3DS.h"
#include <iostream>

int turn = 0;

void display (void) {  
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red  
    glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
    
    Model_3DS m;

    m.Load("C:\\c\\metoritewars\\objects\\player\\test.3ds");	// Load the model
    
    //glTranslatef(0.0,-5.0,-20.0);

    // If you want to show the model's normals
    m.shownormals = true;

    // If the model is not going to be lit then set the lit
    // variable to false. It defaults to true.
    m.lit = false;

    // You can disable the rendering of the model
    m.visible = true;

    // You can move and rotate the model like this:
    m.rot.x = 90.0f;
    m.rot.y = 30.0f;
    m.rot.z = 0.0f;

    m.pos.x = -1.0f;
    m.pos.y = -1.0f;
    m.pos.z = -20.0f;
    
    std::cout << "a" << std::endl;
    
    //m.Draw();	 // Renders the model to the screen
    
    glFlush(); // Flush the OpenGL buffers to the window  
}  
  
void reshape (int width, int height) {  
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}  
  
void keydown (int key){
    
}

int main (int argc, char **argv) {  
    glutInit(&argc, argv); // Initialize GLUT  
    glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)  
    glutInitWindowSize (500, 500); // Set the width and height of the window  
    glutInitWindowPosition (100, 100); // Set the position of the window  
    
    glutCreateWindow ("You're first OpenGL Window"); // Set the title for the window  
    
    glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  
    glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for rendering  
    //glutKeyboardFunc(keydown);
    
    glutMainLoop(); // Enter GLUT's main loop  
} 