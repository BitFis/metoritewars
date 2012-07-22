/* 
 * File:   object.h
 * Author: zurcherl
 *
 * Created on 19. Juli 2012, 14:02
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include "vector3.h"

class object {
public:
    object();
    void draw();
    void setpos(float x, float y, float z);
    void setrot(float x, float y, float z);
    void move(float x, float y, float z);
    void rotate(float x, float y, float z);
    void activate();
    void deactivate();
    object(const object& orig);
    virtual ~object();
    Vector3 transform;
    Vector3 rotation;
private:
    bool active;
    float speed;
};

#endif	/* OBJECT_H */

