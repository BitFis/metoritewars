#include "VoidReceiver.h"

VoidReceiver::VoidReceiver(IrrlichtDevice *device) {
  this->device = device;
  if(device != 0) {
    this->driver = device->getVideoDriver();
    this->smgr = device->getSceneManager();
    this->gui = device->getGUIEnvironment();
  }
}

VoidReceiver::~VoidReceiver() {
}
