
#ifndef KEYBUFFERTEST_H
#define	KEYBUFFERTEST_H

#include "../src/key-buffer.h"

#include <cppunit/extensions/HelperMacros.h>

class KeyBufferTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(KeyBufferTest);
    CPPUNIT_TEST(test_get);
    CPPUNIT_TEST(test_set);
    CPPUNIT_TEST_SUITE_END();
    
    KeyBuffer *keybuffer;
  public:
    void setUp();
    void tearDown();
    
    void test_get();
    void test_set();
};

#endif	/* KEYBUFFERTEST_H */

