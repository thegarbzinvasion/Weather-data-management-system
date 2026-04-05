#ifndef WEATHERDATAPROCESSOR_H
#define WEATHERDATAPROCESSOR_H

//---------------------------------------------------------------------------------

#include <map>
#include "Vector.h"
#include "Bst.h"
#include "MonthlyAggregate.h"
#include "MonthlyData.h"
#include "Menu.h"
#include <string>

//---------------------------------------------------------------------------------

/**
 * @struct ProcessedData
 * @brief Container for all data resulting from map to vector conversion.
 *
 * Holds the final Vector of MonthlyData, BSTs for years and months,
 * and the sPCC cache map for Option 3.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 03/04/2026
 */
struct ProcessedData
{
    Vector<MonthlyData> monthlyData;      ///< Primary storage of monthly statistics
    Bst<int> yearsWithData;               ///< BST of all years that have data
    Bst<int> monthsWithData;              ///< BST of all months that have data
    std::map<int, SPCCResult> spccCache;  ///< Cache for Option 3 sPCC results
};

/**
 * @class WeatherDataProcessor
 * @brief Converts aggregated map data to final Vector storage.
 *
 * Takes a std::map with Month-Year keys and MonthlyAggregate values,
 * calculates averages and standard deviations, and produces a Vector
 * of MonthlyData for primary storage.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 03/04/2026
 */

class WeatherDataProcessor
{
public:
    /**
     * @brief Converts a map of MonthlyAggregate to a ProcessedData struct
     * @param tempMap Map with keys in format "Month-Year" (e.g., "3-2015")
     * @return ProcessedData containing Vector<MonthlyData> and BSTs
     */
    ProcessedData convertToVector(std::map<std::string, MonthlyAggregate>& tempMap);
};

#endif // WEATHERDATAPROCESSOR_H
