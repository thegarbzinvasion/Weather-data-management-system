#ifndef OPTION3SERVICE_H
#define OPTION3SERVICE_H

//---------------------------------------------------------------------------------

#include "WeatherRecord.h"
#include "Vector.h"
#include "StatsCalculator.h"
#include "ConsoleWriter.h"

//---------------------------------------------------------------------------------

/**
 * @class Option3Service
 * @brief Implements menu option 3.
 *
 * Computes monthly total solar radiation for a year
 * and prints results using ConsoleWriter.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 10/02/2026
 */

class Option3Service
{
public:
    /** @brief Constructor */
    Option3Service(const StatsCalculator& stats, const ConsoleWriter& writer);

    /** @brief Executes Option 3 */
    void executeOption3(const Vector<WeatherRecord>& weatherrecords, int year)const;
private:
    const StatsCalculator& m_stats; ///< Reference to StatsCalculator
    const ConsoleWriter& m_writer; ///< Reference to ConsoleWriter
};

#endif // OPTION3SERVICE_H
