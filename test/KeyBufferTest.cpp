
#include "KeyBufferTest.h"

#include <cstdlib>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(KeyBufferTest);

void KeyBufferTest::setUp() {
  keybuffer = new KeyBuffer();
}

void KeyBufferTest::tearDown() {
  delete keybuffer;
}

void KeyBufferTest::testGet() {
  // check if the keys array got properly initialized
  for(int i = 0; i < KEYBUFFER_NUM_KEYS; i++) {
    CPPUNIT_ASSERT(keybuffer->get(i) == false);
  }
}

void KeyBufferTest::testSet() {
  
  bool *map = new bool[KEYBUFFER_NUM_KEYS];
  
  // try turn every but to a random value & check if it's properly set
  for(int i = 0; i < KEYBUFFER_NUM_KEYS; i++) {
    bool new_value = ((float)rand() / (float)RAND_MAX) > 0.5f ? true : false;
    map[i] = new_value;
    keybuffer->set(i, new_value);
    CPPUNIT_ASSERT(keybuffer->get(i) == new_value);
  }
  
  // check if setting one value didn't affect other values
  for(int i = 0; i < KEYBUFFER_NUM_KEYS; i++) {
    CPPUNIT_ASSERT(keybuffer->get(i) == map[i]);
  }
}

