/* 
 * File:   GameMenu.cpp
 * Author: zurcherl
 * 
 * Created on 14. August 2012, 15:47
 */

#include "GameMenu.h"

GameMenu::GameMenu(World* world) : Scene("menu", world) {
  
}

void GameMenu::onLoad(){
  //create own skin
  gui::IGUISkin* skin = gui->getSkin();
  gui::IGUIFont* font = gui->getFont("menufont.bmp");
  
  if(font)
    skin->setFont(font);
  
  skin->setFont(gui->getBuiltInFont(), gui::EGDF_TOOLTIP);
}

bool GameMenu::OnEvent(const SEvent& event){
    
  //get gui events
  if(event.EventType == EET_GUI_EVENT){
    
    //get event id
    s32 id = event.GUIEvent.Caller->getID();
    
    //get button events
    if(event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED){
      if(id == 301){
        device->closeDevice();
      }else if(id == 300){
        world->loadScene("game");
      }
    }
  }
  
  return false;
}

void GameMenu::onTick(){
  
}

void GameMenu::onUnload(){
  
}


