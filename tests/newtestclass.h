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

    CPPUNIT_TEST(testParseData_northernLatitude);
    CPPUNIT_TEST(testParseData_southernLatitude);
    CPPUNIT_TEST(testParseData_easternLongitude);
    CPPUNIT_TEST(testParseData_westernLongitude);
    CPPUNIT_TEST(testParseData_altitude);
    CPPUNIT_TEST(testParseData_time);
    CPPUNIT_TEST(testParseData_speed);
    CPPUNIT_TEST(testParseData_satellites);

    CPPUNIT_TEST(testMinutesToDegrees_5532_82);
    CPPUNIT_TEST(testMinutesToDegrees_5542_2389);
    CPPUNIT_TEST(testMinutesToDegrees_03741_6063);

    CPPUNIT_TEST(testMinutesToDegrees_notEqual_0374_16063);

    CPPUNIT_TEST(testUtcToUnixTime_065504);

    CPPUNIT_TEST(testParseData_partialBuffer_Latitude);
    CPPUNIT_TEST(testParseData_partialBuffer_Longitude);

    CPPUNIT_TEST(testParseData_partialBuffer_Latitude_BufferIsNotFull);
    CPPUNIT_TEST(testParseData_partialBuffer_Longitude_BufferIsNotFull);

    CPPUNIT_TEST(testParseData_partialBuffer_Latitude_twoPackage);
    CPPUNIT_TEST(testParseData_partialBuffer_Longitude_twoPackage);
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

    void testParseData_northernLatitude();
    void testParseData_southernLatitude();
    void testParseData_easternLongitude();
    void testParseData_westernLongitude();

    void testParseData_altitude();
    void testParseData_time();
    void testParseData_speed();
    void testParseData_satellites();

    void testMinutesToDegrees_5532_82();
    void testMinutesToDegrees_5542_2389();
    void testMinutesToDegrees_03741_6063();

    void testMinutesToDegrees_notEqual_0374_16063();
    
    //void testUtcToUnixTime_125504();
    void testUtcToUnixTime_065504();

    void testParseData_partialBuffer_Latitude();
    void testParseData_partialBuffer_Longitude();

    void testParseData_partialBuffer_Latitude_BufferIsNotFull();
    void testParseData_partialBuffer_Longitude_BufferIsNotFull();

    void testParseData_partialBuffer_Latitude_twoPackage();
    void testParseData_partialBuffer_Longitude_twoPackage();
};

#endif	/* NEWTESTCLASS_H */
