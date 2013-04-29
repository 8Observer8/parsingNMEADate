/*
 * File:   newtestclass.h
 * Author: Ivan
 *
 * Created on Apr 25, 2013, 10:40:59 AM
 */

#ifndef NEWTESTCLASS_H
#define	NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testParseData_GGAIsFix_RMCIsFix);
    CPPUNIT_TEST(testParseData_GGAIsNotFix_RMCIsFix);
    CPPUNIT_TEST(testParseData_GGAIsFix_RMCIsNotFix);
    CPPUNIT_TEST(testParseData_GGAIsNotFix_RMCIsNotFix);

    CPPUNIT_TEST(testParseData_latitude);
    CPPUNIT_TEST(testParseData_longitude);
    CPPUNIT_TEST(testParseData_altitude);
    CPPUNIT_TEST(testParseData_time);
    CPPUNIT_TEST(testParseData_speed);
    CPPUNIT_TEST(testParseData_satellites);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testParseData_GGAIsFix_RMCIsFix();
    void testParseData_GGAIsNotFix_RMCIsFix();
    void testParseData_GGAIsFix_RMCIsNotFix();
    void testParseData_GGAIsNotFix_RMCIsNotFix();

    void testParseData_latitude();
    void testParseData_strLatitude();
    void testParseData_longitude();
    void testParseData_altitude();
    void testParseData_time();
    void testParseData_speed();
    void testParseData_satellites();
};

#endif	/* NEWTESTCLASS_H */

