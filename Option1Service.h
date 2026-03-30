#ifndef OPTION1SERVICE_H
#define OPTION1SERVICE_H

//---------------------------------------------------------------------------------

#include "WeatherRecord.h"
#include "Vector.h"
#include "StatsCalculator.h"
#include "ConsoleWriter.h"

//---------------------------------------------------------------------------------

/**
 * @class Option1Service
 * @brief Implements menu option 1.
 *
 * Computes monthly wind speed statistics
 * and displays results using ConsoleWriter.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 08/02/2026
 */


 /**
 * @struct Option1Result
 * @brief Stores calculated wind speed statistics for Option 1.
 *
 * Holds the mean wind speed and sample standard deviation
 * in kilometres per hour.
 */
struct Option1Result
{
    double meanKmh; ///< Average wind speed (km/h)
    double stdDevKmh;  ///< Sample standard deviation (km/h)
};

class Option1Service
{
public:
    /** @brief Constructor */
    Option1Service(const StatsCalculator& stats, const ConsoleWriter& writer);

    /** @brief Executes Option 1 */
    void executeOption1(const Vector<WeatherRecord>& weatherrecords, int year, int month)const;
private:
    const StatsCalculator& m_stats; ///< Reference to StatsCalculator
    const ConsoleWriter& m_writer; ///< Reference to ConsoleWriter
};

#endif // OPTION1SERVICE_H
