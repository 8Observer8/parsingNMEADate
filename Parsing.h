/* 
 * File:   Parsing.h
 * Author: Ivan
 *
 * Created on April 25, 2013, 10:28 AM
 */

#ifndef PARSING_H
#define	PARSING_H

#include <string>
#include <vector>
using namespace std;

struct split {
    enum empties_t {
        empties_ok, no_empties
    };
};

/**
 * The parsing data from the NMEA protocol
 */
class Parsing {
public:
    Parsing();

    bool parseData(std::string buffer);
    
    vector <string> & split(
            vector <string> & result,
            const string& s,
            const string& delimiters,
            split::empties_t empties = split::empties_ok);

    double getLatitude();
    double getLongitude();
    double getAltitude();
    int getTime();
    double getSpeed();
    int getNSatellites();
    bool isFixGPGGA();
    bool isFixGPRMC();

private:
    void setValuesInZero();
    double m_dLatitude;
    double m_dLongitude;
    double m_dAltitude;
    int m_time; // 1970 ml UTC
    double m_dSpeed;
    int m_nSatellites;
};

#endif	/* PARSING_H */
