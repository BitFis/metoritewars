/* 
 * File:   object.cpp
 * Author: lzuercher
 * 
 * Created on 11 August 2012, 09:20
 */

#include "Object.h"

Object::Object() {
  this->model = &this->mesh;
}

void Object::Draw() {
  model->Draw();
}

void Object::loadMesh(char* filename){
  mesh.Load(filename);
}

void Object::copyMesh(Model_3DS &mesh){
  this->mesh = mesh;
}

Object::Object(Model_3DS* model) {
  this->model = model;
}

Object::~Object() {
  
}

