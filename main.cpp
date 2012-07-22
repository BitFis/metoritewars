/*
 *
 * Demonstrates how to load and display an Wavefront OBJ file. 
 * Using triangles and normals as static object. No texture mapping.
 *
 * OBJ files must be triangulated!!!
 * Non triangulated objects wont work!
 * You can use Blender to triangulate
 *
 */

//#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "time-helper.h"
#include "Model_OBJ.h"
#include "vector3.h"
#include "object.h"

#define KEY_ESCAPE 27

using namespace std;

/************************************************************************
  Window
 ************************************************************************/

typedef struct {
    int width;
    int height;
    char title[20];
    
    float field_of_view_angle;
    float z_near;
    float z_far;
} glutWindow;

struct shotstruct{
    object *shots[10];
    unsigned char lastuse;

    float speed;
    
    timespec lastshot;
    double shotimeout;
};

/***************************************************************************
 * Program code
 ***************************************************************************/

Model_OBJ obj;
struct shotstruct shot = {};
float g_rotation;
glutWindow win;

bool Normalkey[256] = {false}; //set key pushed to false

Vector3 Spaceshipos;
Vector3 Spaceshirot;

struct timespec curTime = {};
struct timespec lastTime = {};
double diffTime;

float speed = 80;

void initialize() {
    //init spaceship variables
    Spaceshipos.x = 0.0f;
    Spaceshipos.y = 0.0f;
    Spaceshipos.z = 0.0f;
    Spaceshirot.x = 0.0f;
    Spaceshirot.y = 0.0f;
    Spaceshirot.z = 45.0f;

    //set shot variables
    shot.lastuse = 0;
    shot.shotimeout = 0.2;
    current_utc_time(&shot.lastshot);
    shot.speed = 200;
    
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, win.width, win.height);
    GLfloat aspect = (GLfloat) win.width / win.height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.1f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLfloat amb_light[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat diffuse[] = {0.6, 0.6, 0.6, 1};
    GLfloat specular[] = {0.7, 0.7, 0.3, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void keydown(unsigned char key, int x, int y) {
    Normalkey[key] = true;
}

void keyup(unsigned char key, int x, int y) {
    Normalkey[key] = false;
}

void keyboard() {
    if (Normalkey['w']) {
        Spaceshipos.x -= cos(Spaceshirot.z / 180 * M_PI)*speed*diffTime;
        Spaceshipos.y -= sin(Spaceshirot.z / 180 * M_PI)*speed*diffTime;
    }

    if (Normalkey['s']) {
        Spaceshipos.x += cos(Spaceshirot.z / 180 * M_PI)*speed*diffTime;
        Spaceshipos.y += sin(Spaceshirot.z / 180 * M_PI)*speed*diffTime;
    }

    if (Normalkey['a']) {
        Spaceshirot.z += speed*5*diffTime;
    }

    if (Normalkey['d']) {
        Spaceshirot.z -= speed*5*diffTime;
    }

    if (Normalkey[KEY_ESCAPE]) {
        exit(0);
    }
    
    if (Normalkey[32]){
        //check if he can shoot
        if(shot.shotimeout < timeval_diff(&shot.lastshot, &curTime)){
            current_utc_time(&shot.lastshot);
            
            if(shot.shots[shot.lastuse] == NULL){
                shot.shots[shot.lastuse] = new object();
            }
            shot.shots[shot.lastuse]->setpos(Spaceshipos.x,Spaceshipos.y,0);
            shot.shots[shot.lastuse]->setrot(90,Spaceshirot.z-180,0);
            if(shot.lastuse<9){
                shot.lastuse++;
            }else{
                shot.lastuse = 0;
            }
        }
    }
}

void moveobjects(){
    for(short Count = 0; Count < 10; Count++){
        if(shot.shots[Count] != NULL){
            shot.shots[Count]->move(cos(shot.shots[Count]->rotation.y / 180 * M_PI)*shot.speed*diffTime,sin(shot.shots[Count]->rotation.y / 180 * M_PI)*shot.speed*diffTime, 0);
        }
    }
}

void display() {
    
    lastTime = curTime;
    current_utc_time(&curTime);
    diffTime = timeval_diff(&lastTime, &curTime);
    
    keyboard();

    moveobjects();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 1, 4, 0, 0, 0, 0, 1, 0);
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -70.0f);
    glTranslatef(Spaceshipos.x, Spaceshipos.y, Spaceshipos.z);
    glRotatef(Spaceshirot.x, 1, 0, 0);
    glRotatef(Spaceshirot.y, 0, 1, 0);
    glRotatef(Spaceshirot.z - 90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);

    obj.Draw();
    
    for(short Count = 0; Count < 10; Count++){
        if(shot.shots[Count] != NULL){
            shot.shots[Count]->draw();
        }
    }
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // set window values
    win.width = 640;
    win.height = 480;
    strncpy(win.title, "OpenGL/GLUT OBJ Loader.", 20);
    win.field_of_view_angle = 45;
    win.z_near = 1.0f;
    win.z_far = 500.0f;

    // initialize and run program
    glutInit(&argc, argv); // GLUT initialization
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode
    glutInitWindowSize(win.width, win.height); // set window size
    glutCreateWindow(win.title); // create Window
    glutDisplayFunc(display); // register Display Function
    glutIdleFunc(display); // register Idle Function

    glutKeyboardFunc(keydown); // register Keyboard Handler
    glutKeyboardUpFunc(keyup);

    initialize();

    obj.Load("C:\\cproject\\meteoritewars\\objects\\player\\spaceship.obj");

    current_utc_time(&curTime);
    
    glutMainLoop(); // run GLUT mainloop
    return 0;
}