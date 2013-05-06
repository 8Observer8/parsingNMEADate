/*
 * File:   newtestclass.cpp
 * Author: Ivan
 *
 * Created on Apr 25, 2013, 10:40:59 AM
 */

#include "newtestclass.h"
#include "../Parsing.h"
#include <cmath>
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testParseData_GGAIsFix_RMCIsFix() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots

    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";

    Parsing p;
    bool isParsed = p.parseData(str);
    bool isFix = p.isFixGPGGA() && p.isFixGPRMC();

    CPPUNIT_ASSERT(isFix && isParsed);
}

void newtestclass::testParseData_GGAIsNotFix_RMCIsFix() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots

    std::string str = "$GPGGA,072143.923,,,,,0,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";

    Parsing p;
    bool isParsed = p.parseData(str);
    bool isFix = p.isFixGPGGA() || p.isFixGPRMC();

    CPPUNIT_ASSERT(!isFix && !isParsed);
}

void newtestclass::testParseData_GGAIsFix_RMCIsNotFix() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots

    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,V,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";

    Parsing p;
    bool isParsed = p.parseData(str);
    bool isFix = p.isFixGPGGA() || p.isFixGPRMC();

    CPPUNIT_ASSERT(!isFix && !isParsed);
}

void newtestclass::testParseData_GGAIsNotFix_RMCIsNotFix() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots

    std::string str = "$GPGGA,072143.923,,,,,0,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,V,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";

    Parsing p;
    bool isParsed = p.parseData(str);
    bool isFix = p.isFixGPGGA() && p.isFixGPRMC();

    CPPUNIT_ASSERT(!isFix && !isParsed);
}

void newtestclass::testParseData_satellites() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots
    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";

    Parsing p;
    bool isParsed = p.parseData(str);

    int expected = 3;
    int actual = p.getNSatellites();
    bool isEqual = (expected == actual);

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_latitude() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots

    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";

    Parsing p;
    bool isParsed = p.parseData(str);

    double expected = 5542.2389;
    double actual = p.getLatitude();
    double delta = 0.001;
    
    bool isEqual = (std::abs(expected-actual) <= delta);

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_longitude() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots
    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    bool isParsed = p.parseData(str);

    int expected = 3741.6063;
    int actual = p.getLongitude();
    double delta = 0.0001;

    bool isEqual = (std::abs(expected-actual) <= delta);

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_altitude() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots
    
    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    bool isParsed = p.parseData(str);

    double expected = 9.5;
    double actual = p.getAltitude();
    double delta = 0.1;

    bool isEqual = (std::abs(expected-actual) <= delta);

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_time() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots
    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    bool isParsed = p.parseData(str);

    int expected = 125504;
    int actual = p.getTime();
    
    bool isEqual = (expected == actual);

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_speed() {
    // GPGGA
    // 6) GPS Quality Indicator,
    //    0 - fix not available,
    //    1 - GPS fix,
    //    2 - Differential GPS fix
    // 7) Number of satellites in view, 00 - 12
    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    // GPRMC
    // 1) Time (UTC)
    // 2) Status, V = Navigation receiver warning
    // 3) Latitude
    // 5) Longitude
    // 7) Speed over ground, knots
    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,E,0.06,25.82,200906,,,*17";
    Parsing p;
    bool isParsed = p.parseData(str);

    double expected = 0.06 * 1.852;
    double actual = p.getSpeed();
    double delta = 0.00001;

    bool isEqual = (std::abs(expected-actual) <= delta);

    CPPUNIT_ASSERT(isEqual && isParsed);
}
