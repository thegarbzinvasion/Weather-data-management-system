#ifndef CSVWEATHERLOADER_H
#define CSVWEATHERLOADER_H

//---------------------------------------------------------------------------------

#include "Vector.h"
#include <map>
#include "Bst.h"
#include "WeatherRecord.h"
#include "MonthlyAggregate.h"
#include <string>

//---------------------------------------------------------------------------------

/**
 * @class CSVWeatherLoader
 * @brief Loads and aggregates weather data from CSV files.
 *
 * Reads CSV files line by line, parses headers, extracts weather metrics,
 * and aggregates data directly into monthly statistics using a map.
 * Also stores raw WeatherRecord objects for later MAD calculations.
 *
 * @author Kyaw Okkar
 * @version 02
 * @date 03/04/2026
 */

class CSVWeatherLoader
{
public:
    /**
     * @brief Loads CSV file and aggregates data directly into Map
     * @param csvPath Path to CSV file
     * @param outMap Map to store aggregated monthly data (key: "Month-Year")
     * @param yearsWithData BST to track unique years found in the file
     * @param monthsWithData BST to track unique months found in the file
     * @param outRawRecords Vector to store raw WeatherRecord data (for MAD calculations)
     * @return true if loading successful, false if file cannot be opened or parsing fails
     */
    bool loadData(const std::string& csvPath,
                  std::map<std::string, MonthlyAggregate>& outMap,
                  Bst<int>& yearsWithData,
                  Bst<int>& monthsWithData,
                  Vector<WeatherRecord>& outRawRecords) const;

private:
    /**
     * @brief Normalizes header string by removing spaces and converting to uppercase
     * @param header Raw header string from CSV
     * @return Normalized header string for comparison
     */
    std::string normalizeHeader(const std::string& header) const;
};

#endif // CSVWEATHERLOADER_H
