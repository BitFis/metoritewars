/* 
 * File:   Object.h
 * Author: lzuercher
 *
 * Created on 22 July 2012, 23:38
 */

#ifndef Object_H
#define	Object_H

class Object {
public:
    Object();
    load();
    Object(const Object& orig);
    virtual ~Object();
private:

};

#endif	/* Object_H */

