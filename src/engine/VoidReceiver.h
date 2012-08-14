/* 
 * File:   VoidReceiver.h
 * Author: kuttelm
 *
 * Created on 14. August 2012, 10:06
 */

#ifndef VOIDRECEIVER_H
#define	VOIDRECEIVER_H

#include <irrlicht/irrlicht.h>

using namespace irr;


class VoidReceiver : public IEventReceiver{
  private:
    IrrlichtDevice *device;
  
  public:
    VoidReceiver(IrrlichtDevice *device);
    virtual ~VoidReceiver();

    virtual bool OnEvent(const SEvent& event) = 0;

};

#endif	/* VOIDRECEIVER_H */

