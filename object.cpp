/* 
 * File:   object.cpp
 * Author: zurcherl
 * 
 * Created on 19. Juli 2012, 14:02
 */

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "object.h"
#include "vector3.h"

object::object() {
    this->transform.x = 0.0f;
    this->transform.y = 0.0f;
    this->transform.z = 0.0f;
    this->rotation.x = 0.0f;
    this->rotation.y = 0.0f;
    this->rotation.z = 0.0f;
    
    this->active = true;
    
    this->speed = 200;
}

void object::draw(){
    if(this->active){
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -70.0f);
        glTranslatef(this->transform.x,this->transform.y,this->transform.z);
        
        glRotatef(this->rotation.x,1,0,0);
        glRotatef(this->rotation.y,0,1,0);
        glRotatef(this->rotation.z,0,0,1);
        
        glRotatef(90,0,1,0);
        
        //glutSolidTeapot(3.0f);
        glutSolidCylinder(0.2f,3.0f,12,1);
    }
}

void object::setpos(float x, float y, float z){
    this->transform.x = x;
    this->transform.y = y;
    this->transform.z = z;
}

void object::setrot(float x, float y, float z){
    this->rotation.x = x;
    this->rotation.y = y;
    this->rotation.z = z;
}

void object::move(float x, float y, float z){
    this->transform.x += x;
    this->transform.y += y;
    this->transform.z += z;
}

void object::rotate(float x, float y, float z){
    this->rotation.x += x;
    this->rotation.y += y;
    this->rotation.z += z;
}

void object::activate(){
    this->active = true;
}

void object::deactivate(){
    this->active = false;
}

object::object(const object& orig) {
    
}

object::~object() {
    
}

