/* 
 * File:   object.h
 * Author: lzuercher
 *
 * Created on 22 July 2012, 23:38
 */

#ifndef OBJECT_H
#define	OBJECT_H

class object {
public:
    object();
    load();
    object(const object& orig);
    virtual ~object();
private:

};

#endif	/* OBJECT_H */

