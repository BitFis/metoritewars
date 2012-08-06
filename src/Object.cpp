/* 
 * File:   Object.cpp
 * Author: lzuercher
 * 
 * Created on 06 August 2012, 19:53
 */

// http://www.allegro.cc/forums/thread/605528
// http://openglsamples.sourceforge.net/files/glut_obj.cpp

#include "Object.h"
#include <iostream>
#include <fstream>

using namespace std;

Object::Object() {
}

Object::Object(const char* filename) {
  this->_texture = this->loadObject(filename);
}

GLint Object::loadObject(const char* filename){
  
  ifstream obj;    //object file open and reads all lines of object
  char line[256]; //current line
  
  //open file
  obj.open(filename);
  
  //check if it is open
  if(obj.is_open() == false){    
    cout << "could not open object" << endl;
    return ERROR_FILE_NOT_FOUND;
  }
  
  //read file
  while(obj.eof() == false){
    obj.getline(line, 256);
    
    switch(line[0]){
      case 'o':
        sscanf(line, "o %s", this->_name);
        break;
      
      
        
      default:
        break;
    }
  }
  
  cout << this->_name << endl;
  
  return NOERROR;
}

Object::~Object() {
}

