/* 
 * File:   KeyBuffer.cpp
 * Author: kuttelm
 * 
 * Created on 6. August 2012, 13:45
 */

#include "key-buffer.h"

KeyBuffer::KeyBuffer() {
  keys = new unsigned char[KEYBUFFER_ARRAY_SIZE];
}

KeyBuffer::~KeyBuffer() {
  delete keys;
}

void KeyBuffer::set(unsigned char index, bool value) {
  unsigned char real_index = index / 8;
  unsigned char index_offset = index % 8;
  unsigned char bitmask = 1 << index_offset;
  keys[real_index] = (value) ? keys[real_index] | bitmask : keys[real_index] & ~bitmask;
}

bool KeyBuffer::get(unsigned char index) {
  unsigned char real_index = index / 8;
  unsigned char index_offset = index % 8;
  unsigned char bitmask = 1 << index_offset;
  
  return (bool)((keys[real_index] & bitmask) >> index_offset);
}
