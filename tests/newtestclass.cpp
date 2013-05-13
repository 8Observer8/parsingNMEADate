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
#include <vector>

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

    std::string str = "$GPGGA,072143.923,,,,,0,03,,9.5,M,0.0,M,,0000*5D\r\n"
                      "$GPRMC,125504.049,A,5542.2389,N,03741.600.0,M,,0000*5D\r\n"
                      "$GPRMC,125504.049,A,5542.63,E,0.06,25.82,200906,,,*17";

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

void newtestclass::testParseData_northernLatitude() {
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

    double expected = 55.70398; // 5542.2389
    double actual = p.getLatitude();
    double delta = expected / 1000;

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_southernLatitude() {
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

    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,S,03741.6063,E,0.06,25.82,200906,,,*17";

    Parsing p;
    bool isParsed = p.parseData(str);

    double expected = -55.70398;
    double actual = p.getLatitude();
    double delta = expected / 1000;

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_easternLongitude() {
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

    int expected = 37.693438; // 3741.6063
    int actual = p.getLongitude();
    double delta = 0.00001;

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testParseData_westernLongitude() {
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
    std::string str = "$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,,0000*5D\r\n$GPRMC,125504.049,A,5542.2389,N,03741.6063,W,0.06,25.82,200906,,,*17";
    Parsing p;
    bool isParsed = p.parseData(str);

    int expected = -37.693438;
    int actual = p.getLongitude();
    double delta = expected / 1000;

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

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

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

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

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isParsed);
}

void newtestclass::testMinutesToDegrees_5532_82() {
    double actual;
    double expected = 55.547;
    double delta = 0.001;
    double inputVal = 5532.82;

    Parsing p;
    bool isOk = p.minutesToDegrees(inputVal, actual);

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isOk);
}

void newtestclass::testMinutesToDegrees_5542_2389() {
    double actual;
    double expected = 55.70398;
    double delta = expected / 1000;
    double inputVal = 5542.2389;

    Parsing p;
    bool isOk = p.minutesToDegrees(inputVal, actual);

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isOk);
}

void newtestclass::testMinutesToDegrees_03741_6063() {
    double actual;
    double expected = 37.693438;
    double delta = expected / 1000;
    double inputVal = 03741.6063;

    Parsing p;
    bool isOk = p.minutesToDegrees(inputVal, actual);

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isOk);
}

void newtestclass::testMinutesToDegrees_notEqual_0374_16063() {
    double actual;
    double inputVal = 0374.16063;

    Parsing p;
    bool isOk = p.minutesToDegrees(inputVal, actual);

    CPPUNIT_ASSERT(!isOk);
}

//void newtestclass::testUtcToUnixTime_125504() {
//    double expected = 1158756904;
//    double utcTime = 125504.049;
//    double utcData = 200906;
//
//    Parsing p;
//    double actual = p.utcToUnixTime(utcTime, utcData);
//
//    CPPUNIT_ASSERT_EQUAL(expected, actual);
//}

void newtestclass::testUtcToUnixTime_065504() {
    double expected = 1348124104;
    double utcTime = 065504.049;
    int utcData = 200912;

    Parsing p;
    double actual = p.utcToUnixTime(utcTime, utcData);
    double delta = expected / 1000;

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual);
}

void newtestclass::testParseData_partialBuffer() {
    std::vector<string> qStrings;

    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");

    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");

    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");
    qStrings.push_back("$GPGGA,072143.923,,,,,2,03,,9.5,M,0.0,M,");
    qStrings.push_back(",0000*5D\r\n$GPRMC,125504.049,A,");
    qStrings.push_back("5542.2389,N,03741.6063,E,0.06,");
    qStrings.push_back("25.82,200906,,,*17\r\n");

    std::string s;
    for (unsigned int i = 0; i < 48; i++) {
        s += qStrings[i];
    }
    
    int n = s.length();
    
    Parsing p;
    bool isParsed = true;

    unsigned int i = 0;
    while (i < 32) {
        isParsed = p.parseData(qStrings[i++]);
    }

    double expected = 55.70398; // 5542.2389
    double actual = p.getLatitude();
    double delta = expected / 1000;

    bool isEqual = (std::abs(expected - actual) <= std::abs(delta));

    CPPUNIT_ASSERT(isEqual && isParsed);
}
