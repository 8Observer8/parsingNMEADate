/* 
 * File:   Parsing.cpp
 * Author: Ivan
 * 
 * Created on April 25, 2013, 10:28 AM
 */

#include "Parsing.h"
#include <string>
#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

Parsing::Parsing() {
    m_dLatitude = 0;
    m_dLongitude = 0;
    m_dAltitude = 0;
    m_time = 0;
    m_dSpeed = 0;
    m_nSatellites = 0;
}


// n +
// s -

// e +
// w -



vector <string> & Parsing::split(
        vector <string> & result,
        const string& s,
        const string& delimiters,
        split::empties_t empties) {
    result.clear();
    size_t current;
    size_t next = -1;
    do {
        if (empties == split::no_empties) {
            next = s.find_first_not_of(delimiters, next + 1);
            if (next == string::npos) break;
            next -= 1;
        }
        current = next + 1;
        next = s.find_first_of(delimiters, current);
        result.push_back(s.substr(current, next - current));
    } while (next != string::npos);
    return result;
}

bool Parsing::parseData(std::string s) {
    if (s.empty()) {
        setValuesInZero();
        return false;
    }

    vector<string> fields;
    vector<string>::iterator itGPGGA;
    vector<string> strGPGGA;

    split(fields, s, ",");
    
    // Raplace '\n' to ','
    for (unsigned int i = 0; i < s.size(); ++i) {
        if (s[i] == '\n') {
            s[i] = ',';
        }
    }

    // Take GGA data in array
    itGPGGA = find(fields.begin(), fields.end(), "$GPGGA");
    if (itGPGGA != fields.end()) {
        for (unsigned int i = 0; i < 15; ++i) {
            strGPGGA.push_back(*itGPGGA);
            ++itGPGGA;
        }
    }
    else {
        setValuesInZero();
        return false;
    }
    
    // 6) GPS Quality Indicator,
    // 0 - fix not available,
    // 1 - GPS fix,
    // 2 - Differential GPS fix
    if (strGPGGA[6] == "0") {
        setValuesInZero();
        return false;
    }

    // 7) Number of satellites in view, 00 - 12
    stringstream convertNSatellites(strGPGGA[7]);
    if (!(convertNSatellites >> m_nSatellites)) {
        setValuesInZero();
        return false;
    }

    // 9) Antenna Altitude above/below mean-sea-level (geoid)
    stringstream convertAltitude(strGPGGA[9]);
    if (!(convertAltitude >> m_dAltitude)) {
        setValuesInZero();
        return false;
    }

    // $GPRMC
    vector<string>::iterator itGPRMC;
    vector<string> strGPRMC;
    itGPRMC = find(fields.begin(), fields.end(), "$GPRMC");
    if (itGPRMC != fields.end()) {
        for (unsigned int i = 0; i < 12; ++i) {
            strGPRMC.push_back(*itGPRMC);
            ++itGPRMC;
        }
    }
    else {
        setValuesInZero();
        return false;
    }

    // 2) Status, V = Navigation receiver warning
    if (strGPRMC[2] == "V") {
        setValuesInZero();
        return false;
    }

    // 1) Time (UTC)
    stringstream convertTime(strGPRMC[1]);
    if (!(convertTime >> m_time)) {
        setValuesInZero();
        return false;
    }
    
    // 3) Latitude
    stringstream convertLatitude(strGPRMC[3]);
    if (!(convertLatitude >> m_dLatitude)) {
        setValuesInZero();
        return false;
    }
    
    // 5) Longitude
    stringstream convertLongitude(strGPRMC[5]);
    if (!(convertLongitude >> m_dLongitude)) {
        setValuesInZero();
        return false;
    }

    // 7) Speed over ground, knots
    stringstream convertSpeed(strGPRMC[7]);
    if (!(convertSpeed >> m_dSpeed)) {
        setValuesInZero();
        return false;
    }
}

double Parsing::getLatitude() {
    return m_dLatitude;
}

double Parsing::getLongitude() {
    return m_dLongitude;
}

double Parsing::getAltitude() {
    return m_dAltitude;
}

int Parsing::getTime() {
    return m_time;
}

double Parsing::getSpeed() {
    return m_dSpeed;
}

int Parsing::getNSatellites() {
    return m_nSatellites;
}

void Parsing::setValuesInZero() {
    m_dLatitude = 0;
    m_dLongitude = 0;
    m_dAltitude = 0;
    m_time = 0;
    m_dSpeed = 0;
    m_nSatellites = 0;
}
