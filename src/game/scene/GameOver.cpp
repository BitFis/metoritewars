/* 
 * File:   GameOver.cpp
 * Author: zurcherl
 * 
 * Created on 28. August 2012, 09:33
 */

#include "GameOver.h"


GameOver::GameOver(World* world) : Scene("over", world) {
  
}

void GameOver::onLoad(){
  std::cout << "HALLO?" << endl;
}

bool GameOver::OnEvent(const SEvent& event){
  world->loadScene("menu");
  
  return true;
}

void GameOver::onTick(){
  
}

void GameOver::onUnload(){
  
}

