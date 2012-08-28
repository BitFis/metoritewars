#include "GameScene.h"

GameScene::GameScene(World *world) : Scene("game", world){
  
};

void GameScene::onLoad(){
  ship = new Ship("objects/player/ship.x", this->smgr, this->driver);
  this->meteors = new vector<Meteor*>(0);
  
  camera = smgr->addCameraSceneNode(0,core::vector3df(0.0,0.0,2.0),core::vector3df(0.0,0.0,0.0),1,true);
  smgr->setAmbientLight(video::SColorf(0.1,0.1,0.1,1));
  
  //set points to 0
  points = 0;
  
  //enabling light
  light = smgr->addLightSceneNode(smgr->getRootSceneNode(), core::vector3df(0,0,0.2f), video::SColorf(0.3f,0.3f,0.3f), 5.0f); 
  
  last_meteor_created_at = device->getTimer()->getTime();
  
  gui->getSkin()->setColor(gui::EGDC_BUTTON_TEXT,video::SColor(255, 255, 255, 255));
  gui->getSkin()->setSize(gui::EGDS_BUTTON_HEIGHT, 500);
  
  //reset to normal font
  gui->getSkin()->setFont(gui->getBuiltInFont(), gui::EGDF_DEFAULT);
  
  core::stringw tempPoints = L"Points: ";
  
  tempPoints.append(convertInt(points).c_str());
  
  counterBox = gui->addStaticText((tempPoints.c_str()), core::rect<s32>(20,20,350,40), false, false, 0, GAME_POINT_BOX);
  
  
  //background
  background = new Background(smgr, driver);
}

bool GameScene::OnEvent(const SEvent& event){
  
  return false;
}

void GameScene::onTick(){
  
  bool gameover = false;
  
  //update points
  core::stringw tempPoints = L"Points: ";
  tempPoints.append(convertInt(points).c_str());
  counterBox->setText(tempPoints.c_str());
  
  background->returnStars()->setPosition(ship->getShipNode()->getPosition() + core::vector3df(2.5,-6.0,0.0));
  
  //update ship
  core::vector3df pos;
  ship->update(world->getFrameDeltaTime());
  pos = ship->getPosVec3df();
  pos.Z = camera->getPosition().Z;
  
  camera->setPosition(pos);
  camera->setTarget(ship->getPosVec3df());
  
  //setting light
  pos.Z = light->getPosition().Z;
  
  light->setPosition(pos);
  
  Meteor::setSpawnOffset(ship->getPosVec3df());
  
   
  //Draw life box
  driver->draw2DRectangle(video::SColor(100,150,150,150), 
          core::rect<s32>(driver->getScreenSize().Width-210, 20, 
                          driver->getScreenSize().Width-10, 30));
  
  //Draw life points
  driver->draw2DRectangle(video::SColor(100,255,24,24), 
          core::rect<s32>(driver->getScreenSize().Width-210, 21, 
                          driver->getScreenSize().Width-210+((int)ship->getLifeInProzent()*2), 29));
  
  /////////////////////////////////////////
  //shoot
  
  if(world->getKeys()->get(KEY_SPACE)){
    ship->shoot(world->getRunTime());
  }
  
  ////////////////////////////////////////
  //move ship forward
  if(world->getKeys()->get(KEY_KEY_W)){
    ship->moveFor();
  }
  
  //move ship back
  if(world->getKeys()->get(KEY_KEY_S)){
    ship->moveBack();
  }
  
  if(world->getKeys()->get(KEY_KEY_A)){
    ship->rotate(1, world->getFrameDeltaTime());
  }
  
  //rotate ship
  if(world->getKeys()->get(KEY_KEY_D)){
    ship->rotate(-1, world->getFrameDeltaTime());
  }
  
  /* spawn new meteor every 500 ms*/
  unsigned int tick = device->getTimer()->getTime();
  int count = (tick - last_meteor_created_at) / 100;
  if(count) {
    last_meteor_created_at = tick;
    for(int i = 0; i < count; i++) {
      this->meteors->push_back(new Meteor(smgr));
    }
  }
  
  vector<scene::ISceneNode*>::iterator shot_last_it;
  vector<scene::ISceneNode*> &shots = ship->getShots()->getShotNode();
  
  //(*this->meteors)[0].getMesh()->getScale();
  
  /* check for collisions between meteors */
  foreach(it_meteor1, (*this->meteors)) {
    foreach(it_meteor2, (*this->meteors)) {
      if(*it_meteor1 != *it_meteor2) {
        if((*it_meteor1)->collidesWith((*it_meteor2))) {
          (*it_meteor1)->bounceOf(*it_meteor2);
        }
      }
    }
    
    shot_last_it = shots.begin();
    //check if it collided with a shot of the ship
    foreach(shot, shots){
      
      //remove shot if it is outside of the ring
      if(tooFarAwayFrom((*shot), ship->getPosVec3df(), 2.3f)){
        ship->getShots()->removeShot(shot);
        shot = shot_last_it;
      }else if((*it_meteor1)->collidesWith((*shot), 1.0)){
        //removing shot if it hit a meteor
        ship->getShots()->removeShot(shot);
        shot = shot_last_it;
        (*it_meteor1)->createExplosion();
        //delete meteor by setting it outside of the ring
        (*it_meteor1)->getMesh()->setPosition(ship->getPosVec3df()+core::vector3df(100.0,100.0,100.0));
        //update points
        points++;
      } else {
        shot_last_it = shot;
      }
    }
    
    //check if it collided with the ship
    if((*it_meteor1)->collidesWith((ship->getShipNode()), 1.0)){
      //remove meteor
      (*it_meteor1)->getMesh()->setPosition(ship->getPosVec3df()+core::vector3df(100.0,100.0,100.0));
      //take lives from the ship
      float tempScale = (*it_meteor1)->getMesh()->getScale().X;
      
      //if ship destroyed load gameover scene
      if(ship->takelifepoints((int)(tempScale * 5000))){
        gameover = true;
      }
    }
    
  }
  
  /* remove old meteors */
  Meteor *meteor;
  vector<Meteor*>::iterator last_it = this->meteors->begin();
  foreach(it_meteor, (*this->meteors)) {
    meteor = *it_meteor;
    if(tooFarAwayFrom(meteor->getMesh(), ship->getPosVec3df(), 2.3f)) {
      this->meteors->erase(it_meteor);
      smgr->addToDeletionQueue(meteor->getMesh());
      it_meteor = last_it;
    } else {
      last_it = it_meteor;
      meteor->update(world->getFrameDeltaTime());
    }
  }
  
  if(gameover){
    world->loadScene("over");
  }
}

void GameScene::onUnload(){
  counterBox->remove();
  
  delete background;
  
  light->remove();
  
  delete ship;
  foreach(meteor, (*this->meteors)) {
    delete (*meteor);
  }
  delete meteors;
}

string GameScene::convertInt(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

bool GameScene::tooFarAwayFrom(scene::IAnimatedMeshSceneNode* mesh, core::vector3df pos, float distance) {
  return fabs(distance) < fabs(mesh->getPosition().getDistanceFrom(pos));
}

bool GameScene::tooFarAwayFrom(scene::ISceneNode* mesh, core::vector3df pos, float distance) {
  return fabs(distance) < fabs(mesh->getPosition().getDistanceFrom(pos));
}

