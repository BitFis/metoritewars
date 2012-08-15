/* 
 * File:   KeyBuffer.cpp
 * Author: kuttelm
 * 
 * Created on 6. August 2012, 13:45
 */

#include "KeyBuffer.h"
#include <iostream>

using namespace std;

KeyBuffer::KeyBuffer() {
  array_size = ceil(KEY_KEY_CODES_COUNT/(float)(sizeof(unsigned char) * 8));
  keys = new unsigned char[array_size];
  for(int i = 0; i < (int)array_size; i++) {
    keys[i] = 0;
  }
}

KeyBuffer::~KeyBuffer() {
  delete keys;
}

void KeyBuffer::set(unsigned int index, bool value) {
  if(index < (array_size * 8)) {
    unsigned int real_index = index / 8;
    unsigned char index_offset = index % 8;
    unsigned char bitmask = 1 << index_offset;
    keys[real_index] = (value) ? keys[real_index] | bitmask : keys[real_index] & ~bitmask;
  }
}

bool KeyBuffer::get(unsigned int index) {
  if(index < (array_size * 8)) {
    unsigned int real_index = index / 8;
    unsigned char index_offset = index % 8;
    unsigned char bitmask = 1 << index_offset;

    return (bool)((keys[real_index] & bitmask) >> index_offset);
  }
  return false;
}


void KeyBuffer::special_key(unsigned int index, bool value) {
  if(index < KEYBUFFER_SPECIAL_KEYS_NUM) {
    special_keys[index] = value;
  }
}

bool KeyBuffer::special_key(unsigned int index) {
  if(index < KEYBUFFER_SPECIAL_KEYS_NUM) {
    return special_keys[index];
  }
  return false;
}

void KeyBuffer::control(bool value) {
  special_key(KEYBUFFER_SPECIAL_CONTROL, value);
}

bool KeyBuffer::control() {
  return special_key(KEYBUFFER_SPECIAL_CONTROL);
}

void KeyBuffer::shift(bool value) {
  special_key(KEYBUFFER_SPECIAL_SHIFT, value);
}

bool KeyBuffer::shift() {
  return special_key(KEYBUFFER_SPECIAL_SHIFT);
}
