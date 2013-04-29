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
 * The parsing of the data from the NMEA protocol
 */
class Parsing {
public:
    /**
     * The constructor
     */
    Parsing();

    /**
     * Parses the data from the NMEA protocol
     * 
     * @param buffer The buffer for parsing
     * @return The analysis occurred or not
     */
    bool parseData(std::string buffer);

    /**
     * Splits this string
     * 
     * @param result The result
     * @param inputBuffer The input buffer
     * @param delimiters The delimiter
     * @param empties Include or not the empty strings
     * @return The result
     */
    vector <string> & split(
            vector <string> & result,
            const string& inputBuffer,
            const string& delimiters,
            split::empties_t empties = split::empties_ok);

    /**
     * Gets the latitude
     * 
     * @return The latitude
     */
    double getLatitude();

    /**
     * Gets the longitude
     * 
     * @return The longitude
     */
    double getLongitude();

    /**
     * Gets the altitude
     * 
     * @return The altitude
     */
    double getAltitude();

    /**
     * Gets the time
     * 
     * @return The time
     */
    int getTime();

    /**
     * Gets the speed
     * 
     * @return The speed
     */
    double getSpeed();

    /**
     * Gets the numbers of the satellites
     * 
     * @return The numbers of the satellites
     */
    int getNSatellites();

    /**
     * Checks is fix or not the GPGGA
     * 
     * @return The GPGGA is fix or not
     */
    bool isFixGPGGA();

    /**
     * Checks is fix or not the GPRMC
     * 
     * @return The GPRMC is fix or not
     */
    bool isFixGPRMC();

private:
    /**
     * Sets the values in zero
     */
    void setValuesInZero();
    
    /**
     * The latitude
     */
    double m_dLatitude;

    /**
     * The longitude
     */
    double m_dLongitude;

    /**
     * The altitude
     */
    double m_dAltitude;

    /**
     * The time
     */
    int m_time; // 1970 ml UTC

    /**
     * The speed
     */
    double m_dSpeed;

    /**
     * The number of the satellites
     */
    int m_nSatellites;
};

#endif	/* PARSING_H */
