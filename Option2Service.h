#ifndef OPTION2SERVICE_H
#define OPTION2SERVICE_H

//---------------------------------------------------------------------------------

#include "WeatherRecord.h"
#include "Vector.h"
#include "StatsCalculator.h"
#include "ConsoleWriter.h"

//---------------------------------------------------------------------------------

/**
 * @class Option2Service
 * @brief Implements menu option 2.
 *
 * Computes monthly ambient air temperature statistics
 * for a given year and displays results using ConsoleWriter.
 *
 * Contains no direct input/output logic besides calling ConsoleWriter.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 09/02/2026
 */

/**
 * @struct Option2Result
 * @brief Stores calculated temperature statistics for Option 2.
 *
 * Holds the mean ambient air temperature and
 * sample standard deviation in degrees Celsius.
 */
struct Option2Result
{
    double meanC; ///< Average temperature (C)
    double stdDevC;  ///< Sample standard deviation (C)
};

class Option2Service
{
public:
    /** @brief Constructor */
    Option2Service(const StatsCalculator& stats, const ConsoleWriter& writer);

    /** @brief Executes Option 2 */
    void executeOption2(const Vector<WeatherRecord>& weatherrecords, int year)const;
private:
    const StatsCalculator& m_stats; ///< Reference to StatsCalculator
    const ConsoleWriter& m_writer; ///< Reference to ConsoleWriter
};

#endif // OPTION2SERVICE_H
