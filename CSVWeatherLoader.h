#ifndef CSVWEATHERLOADER_H
#define CSVWEATHERLOADER_H

//---------------------------------------------------------------------------------

#include "Vector.h"
#include "WeatherRecord.h"
#include <string>

//---------------------------------------------------------------------------------

/**
 * @class CSVWeatherLoader
 * @brief Loads weather records from a CSV file.
 *
 * Reads CSV data and converts it into WeatherRecord objects
 * stored inside a Vector.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 28/02/2026
 */

class CSVWeatherLoader
{
public:
    /**
     * @brief Loads data from CSV file
     * @return bool True if loading successful
     */
    bool loadData(const std::string & csvPath, Vector<WeatherRecord> & outweatherrecords) const;
};

#endif // CSVWEATHERLOADER_H
