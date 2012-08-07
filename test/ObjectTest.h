/* 
 * File:   ObjectTest.h
 * Author: zurcherl
 *
 * Created on 7. August 2012, 11:23
 */

#ifndef OBJECTTEST_H
#define	OBJECTTEST_H

class ObjectTest : public CppUnit::TestFixture {
  private:
    CPPUNIT_TEST_SUITE(ObjectTest);
    CPPUNIT_TEST(testLoadObject);
    CPPUNIT_TEST(testCalculateNormals);
    CPPUNIT_TEST_SUITE_END();
    
    Object *obj;
  public:
    void setUp();
    void tearDown();
    
    void testLoadObject();
    void testCalculateNormals();
};

#endif	/* OBJECTTEST_H */

