#ifndef VOIDRECEIVER_H
#define	VOIDRECEIVER_H

#include <irrlicht/irrlicht.h>

using namespace irr;


class VoidReceiver : public IEventReceiver{
  protected:
    IrrlichtDevice *device;
    video::IVideoDriver *driver;
    scene::ISceneManager *smgr;
    gui::IGUIEnvironment *gui;
  
  public:
    
    VoidReceiver(IrrlichtDevice *device);
    virtual ~VoidReceiver();

    virtual bool OnEvent(const SEvent& event) = 0;

};

#endif	/* VOIDRECEIVER_H */

