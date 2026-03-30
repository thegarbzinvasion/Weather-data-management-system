#ifndef CONTROLLER_H
#define CONTROLLER_H

//---------------------------------------------------------------------------------

#include <string>
#include "Vector.h"
#include "WeatherRecord.h"
#include "DataSourceReader.h"
#include "CSVWeatherLoader.h"
#include "StatsCalculator.h"
#include "ConsoleWriter.h"
#include "CSVReportWriter.h"
#include "Menu.h"
#include "Option1Service.h"
#include "Option2Service.h"
#include "Option3Service.h"
#include "Option4Service.h"

//---------------------------------------------------------------------------------

/**
 * @class Controller
 * @brief Controls overall program flow.
 *
 * Loads data, processes menu requests,
 * and coordinates between services.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 18/02/2026
 */

class Controller
{
public:
    /** @brief Starts and runs the full program */
    void runProgram();
private:
    /**
     * @brief Loads all weather data from CSV
     * @return bool True if loading successful
     */
    bool loadAllData(Vector<WeatherRecord>& outRecords) const;   ///< Private helper
    /**
     * @brief Builds full CSV file path
     * @return std::string */
    std::string buildCsvPath(const std::string& fileName) const;  ///< Private helper
};

#endif // CONTROLLER_H
