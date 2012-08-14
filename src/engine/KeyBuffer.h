#ifndef KEYBUFFER_H
#define	KEYBUFFER_H

#include <irrlicht/irrlicht.h>

using namespace irr;

#define KEYBUFFER_SPECIAL_CONTROL  0
#define KEYBUFFER_SPECIAL_SHIFT    1
#define KEYBUFFER_SPECIAL_KEYS_NUM 2

class KeyBuffer {
  private:
    unsigned char *keys;
    
    bool special_keys[KEYBUFFER_SPECIAL_KEYS_NUM];
    
    void special_key(unsigned int index, bool value);
    bool special_key(unsigned int index);

    
  public:
    
    unsigned int array_size;
    KeyBuffer();
    ~KeyBuffer();
    
    void set(unsigned int index, bool value);
    bool get(unsigned int index);

        
    void control(bool value);
    bool control();

    void shift(bool value);
    bool shift();

};

#endif	/* KEYBUFFER_H */

