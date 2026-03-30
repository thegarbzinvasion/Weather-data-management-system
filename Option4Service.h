#ifndef OPTION4SERVICE_H
#define OPTION4SERVICE_H

//---------------------------------------------------------------------------------

#include "WeatherRecord.h"
#include "Vector.h"
#include "StatsCalculator.h"
#include "CSVReportWriter.h"

//---------------------------------------------------------------------------------

/**
 * @class Option4Service
 * @brief Implements menu option 4.
 *
 * Generates a yearly summary including wind,
 * temperature, and solar radiation data,
 * and writes the results to a CSV file.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 12/02/2026
 */

/**
 * @struct Option4Result
 * @brief Stores monthly summary statistics for Option 4.
 *
 * Contains wind, temperature, and solar radiation results
 * for a specific month of a selected year.
 */
struct Option4Result
{
    int month; ///< Month number (1�12)
    bool hasWind; ///< True if wind data exists
    double meanWindKmh; ///< Mean wind speed (km/h)
    double stdWindKmh; ///< Wind standard deviation (km/h)
    bool hasTemp; ///< True if temperature data exists
    double meanTempC; ///< Mean temperature (C)
    double stdTempC; ///< Temperature standard deviation (C)
    bool hasSolar; ///< True if solar data exists
    double totalSolarKWhPerM2;  ///< Total solar radiation (kWh/m2)
};

class Option4Service
{
public:
    /** @brief Constructor */
    Option4Service(const StatsCalculator& stats, const CSVReportWriter& writer);

    /** @brief Executes Option 4 */
    void executeOption4(const Vector<WeatherRecord>& weatherrecords, int year, const std::string& outFile) const;
private:
    const StatsCalculator& m_stats; ///< Reference to StatsCalculator
    const CSVReportWriter& m_writer; ///< Reference to ConsoleWriter
};

#endif // OPTION4SERVICE_H
