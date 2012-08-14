#include <irrlicht/irrlicht.h>
#include "engine/World.h"
#include "game/scene/GameMenu.h"

using namespace irr;

int main() {
  
  World *world = new World();
  IrrlichtDevice* device = createDevice(video::EDT_OPENGL,
          core::dimension2d<u32 > (1024, 768), 16, false, true, false, world);
  if (device == 0) {
    return 1; // could not create selected driver.
  }

  world->setDevice(device);
  
  //create scene
  GameMenu* menu = new GameMenu(world);

  
  //add scenes
  world->addScene(menu);
  
  //load menu scene
  world->loadScene("menu");
  
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  int lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();
  
  while (device->run()) {
    //Work out a frame delta time.
    const u32 now = device->getTimer()->getTime();
    const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
    then = now;

     
    driver->beginScene(true, true, video::SColor(255, 113, 113, 133));
    
    if(world->hasCurrentScene()) {
      world->getCurrentScene()->onTick();
    }
    
    smgr->drawAll(); // draw the 3d scene
    device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
    driver->endScene();

    
    int fps = driver->getFPS();
    if (lastFPS != fps)
    {
      core::stringw tmp(L"Movement Example - Irrlicht Engine [");
      tmp += driver->getName();
      tmp += L"] fps: ";
      tmp += fps;

      device->setWindowCaption(tmp.c_str());
      lastFPS = fps;
    }
  }

  delete menu;
  
  /*
  In the end, delete the Irrlicht device.
   */
  device->drop();

  return 0;
}

/*
That's it. Compile and play around with the program.
 **/
