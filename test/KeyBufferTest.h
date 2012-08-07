
#ifndef KEYBUFFERTEST_H
#define	KEYBUFFERTEST_H

#include "../src/KeyBuffer.h"

#include <cppunit/extensions/HelperMacros.h>

class KeyBufferTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(KeyBufferTest);
    CPPUNIT_TEST(testGet);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST_SUITE_END();
    
    KeyBuffer *keybuffer;
  public:
    void setUp();
    void tearDown();
    
    void testGet();
    void testSet();
};

#endif	/* KEYBUFFERTEST_H */

