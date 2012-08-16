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
  
  device->getGUIEnvironment()->addButton(core::rect<s32>(world->win.width/2 - 300/2,200,300/2 + world->win.width/2,200 + 80), 0, MENU_START_GAME, L"Start", L"Starts Game");
  device->getGUIEnvironment()->addButton(core::rect<s32>(world->win.width/2 - 300/2,290,300/2 + world->win.width/2,290 + 80), 0, MENU_EXIT_BUTTON, L"Quit", L"Exits Program");
}

bool GameMenu::OnEvent(const SEvent& event){
    
  //get gui events
  if(event.EventType == EET_GUI_EVENT){
    
    //get event id
    s32 id = event.GUIEvent.Caller->getID();
    
    //get button events
    if(event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED){
      if(id == MENU_EXIT_BUTTON){
        device->closeDevice();
      }else if(id == MENU_START_GAME){
        world->loadScene("game");
      }
    }
  }
  
  return false;
}

void GameMenu::onTick(){
  
}

void GameMenu::onUnload(){
  gui->clear();
}


