#ifndef CSVREPORTWRITER_H
#define CSVREPORTWRITER_H

//---------------------------------------------------------------------------------

#include <string>
#include "Vector.h"
#include "MonthlyData.h"
#include "WeatherRecord.h"

//---------------------------------------------------------------------------------

/**
 * @class CSVReportWriter
 * @brief Writes yearly summary data to a CSV file.
 *
 * Exports formatted monthly statistics including wind speed,
 * temperature, and solar radiation with standard deviation
 * and mean absolute deviation (MAD).
 *
 * @author Kyaw Okkar
 * @version 02
 * @date 03/04/2026
 */

class CSVReportWriter
{
public:
    /**
     * @brief Writes monthly statistics for a specified year to CSV file
     * @param filename Output file name (e.g., "WindTempSolar.csv")
     * @param year Year to write data for
     * @param monthlyData Vector of all aggregated monthly data
     * @param rawRecords Raw weather records for MAD calculations
     * @return true if write successful, false if file cannot be opened
     */
    bool writeOption4(const std::string& filename,
                      int year,
                      const Vector<MonthlyData>& monthlyData,
                      const Vector<WeatherRecord>& rawRecords) const;

private:
    /**
     * @brief Converts month number to month name
     * @param month Month number (1-12)
     * @return Month name string (e.g., "January" for 1)
     */
    std::string monthName(int month) const;
};

#endif // CSVREPORTWRITER_H
