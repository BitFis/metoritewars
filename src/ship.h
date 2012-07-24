/* 
 * File:   Ship.h
 * Author: lzuercher
 *
 * Created on 22 July 2012, 23:56
 */

#ifndef Ship_H
#define	Ship_H

#include "Object.h"


class Ship : Object{
public:
    Ship();
    Ship(const Ship& orig);
    virtual ~Ship();
private:
};

#endif	/* Ship_H */

