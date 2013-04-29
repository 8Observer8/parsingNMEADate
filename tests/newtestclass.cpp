/*
 * File:   newtestclass.cpp
 * Author: Ivan
 *
 * Created on Apr 25, 2013, 10:40:59 AM
 */

#include "newtestclass.h"
#include "../Parsing.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

#include <string>

void newtestclass::testParseData_normalTest() {
    std::string str = "\n$GPGGA,072143.923,,,,,0,00,,,M,0.0,M,,0000*5D\t\n$GPGSA,A,1,,,,,,,,,,,,,,,*1E\t\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    p.parseData(str);

    int expected = 55;
    int actual = p.getLatitude();
    
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}

void newtestclass::testParseData_latitude() {
    std::string str = "$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    p.parseData(str);

    int expected = 55;
    int actual = p.getLatitude();
    
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}

void newtestclass::testParseData_longitude() {
    std::string str = "$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    p.parseData(str);

    int expected = 37;
    int actual = p.getLongitude();
    
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}

void newtestclass::testParseData_altitude() {
    std::string str = "$GPGGA,072143.923,,,,,0,00,,5.6,M,0.0,M,,0000*5D";
    Parsing p;
    p.parseData(str);

    double expected = 5.6;
    double actual = p.getAltitude();
    double delta = 0.000001;
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta);
}

void newtestclass::testParseData_time() {
    std::string str = "$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    p.parseData(str);

    int expected = 125504;
    int actual = p.getTime();
    
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}

void newtestclass::testParseData_speed() {
    std::string str = "$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    p.parseData(str);

    double expected = 0.06;
    double actual = p.getSpeed();
    double delta = 0.000001;
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta);
}

void newtestclass::testParseData_satellites() {
    std::string str = "$$GPGGA,072143.923,,,,,0,03,,,M,0.0,M,,0000*5D";
    Parsing p;
    p.parseData(str);

    int expected = 3;
    int actual = p.getNSatellites();
    
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}
