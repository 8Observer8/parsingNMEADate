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
    setValuesInZero();
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

void print(const vector<string>& s) {
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == "") {
            cout << "\"\"" << endl;
        } else {
            cout << s[i] << endl;
        }
    }
}

#include <fstream>

void printInFile(const vector<string>& s) {
    ofstream myfile;
    myfile.open("testOutputFile.txt");
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == "") {
            myfile << "\"\"" << endl;
        } else {
            myfile << s[i] << endl;
        }
    }
    myfile.close();
}

bool Parsing::parseData(std::string s) {
    if (s.empty()) {
        setValuesInZero();
        return false;
    }

    vector<string> fields;
    vector<string>::iterator itGPGGA;
    vector<string> strGPGGA;

    // Raplace '\n' to ','
    for (unsigned int i = 0; i < s.size(); ++i) {
        if (s[i] == '\n') {
            s[i] = ',';
        }
    }

    split(fields, s, ",");

    // Take GGA data in array
    itGPGGA = find(fields.begin(), fields.end(), "$GPGGA");
    if (itGPGGA != fields.end()) {
        for (unsigned int i = 0; i < 15; ++i) {
            if (itGPGGA != fields.end()) {
                strGPGGA.push_back(*itGPGGA);
                ++itGPGGA;
            }
            else {
                setValuesInZero();
                return false;
            }
        }
    } else {
        setValuesInZero();
        return false;
    }

    // 6) GPS Quality Indicator,
    // 0 - fix not available,
    // 1 - GPS fix,
    // 2 - Differential GPS fix
    if (strGPGGA[6] != "2") {
        setValuesInZero();
        return false;
    } else {
        m_isFixGPGGA = true;
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

    // Take the GPRMC packet
    vector<string>::iterator itGPRMC;
    vector<string> strGPRMC;
    itGPRMC = find(fields.begin(), fields.end(), "$GPRMC");
    if (itGPRMC != fields.end()) {
        for (unsigned int i = 0; i < 12; ++i) {
            if (itGPRMC != fields.end()) {
                strGPRMC.push_back(*itGPRMC);
                ++itGPRMC;
            } else {
                setValuesInZero();
                return false;
            }
        }
    } else {
        setValuesInZero();
        return false;
    }
    //    print(fields);
    //    printInFile(fields);

    // 2) Status, V = Navigation receiver warning
    if (strGPRMC[2] != "A") {
        setValuesInZero();
        return false;
    } else {
        m_isFixGPRMC = true;
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
    
    // 4) N or S
    if (strGPRMC[4] == "S") {
        m_dLatitude *= -1;
    }

    // 5) Longitude
    stringstream convertLongitude(strGPRMC[5]);
    if (!(convertLongitude >> m_dLongitude)) {
        setValuesInZero();
        return false;
    }

    // 6) E or W
    if (strGPRMC[6] == "W") {
        m_dLongitude *= -1;
    }

    // 7) Speed over ground, knots
    stringstream convertSpeed(strGPRMC[7]);
    if (!(convertSpeed >> m_dSpeed)) {
        setValuesInZero();
        return false;
    }
    m_dSpeed *= 1.852;

    return true;
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

bool Parsing::isFixGPGGA() {
    return m_isFixGPGGA;
}

bool Parsing::isFixGPRMC() {
    return m_isFixGPRMC;
}

void Parsing::setValuesInZero() {
    m_dLatitude = 0;
    m_dLongitude = 0;
    m_dAltitude = 0;
    m_time = 0;
    m_dSpeed = 0;
    m_nSatellites = 0;
    m_isFixGPGGA = false;
    m_isFixGPRMC = false;
}
