#ifndef KEYBUFFER_H
#define	KEYBUFFER_H

#define KEYBUFFER_CHAR_SIZE (sizeof(unsigned char))
#define KEYBUFFER_NUM_KEYS 256
#define KEYBUFFER_ARRAY_SIZE (KEYBUFFER_NUM_KEYS/KEYBUFFER_CHAR_SIZE)

class KeyBuffer {
  private:
    unsigned char *keys;
    
  public:
    KeyBuffer();
    ~KeyBuffer();
    
    void set(unsigned char index, bool value);
    bool get(unsigned char index);


};

#endif	/* KEYBUFFER_H */

