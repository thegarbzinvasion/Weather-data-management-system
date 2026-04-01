#ifndef CSVREPORTWRITER_H
#define CSVREPORTWRITER_H

//---------------------------------------------------------------------------------

#include <string>
#include "Vector.h"

//---------------------------------------------------------------------------------

/**
 * @class CSVReportWriter
 * @brief Writes yearly summary data to a CSV file.
 *
 * Used by Option4Service to export
 * formatted monthly statistics.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 15/02/2026
 */

struct Option4Result; ///< Forward Declaration of Struct by telling Compiler It Exists

class CSVReportWriter
{
public:
    /**
     * @brief Writes Option 4 results to CSV file
     * @return bool True if writing successful
     */
    bool writeOption4(const std::string & filename, int year, const Vector<Option4Result>& summaries) const;

private:
    /**
     * @brief Converts month number to month name
     * @return std::string */
    std::string MonthName(int month) const; // private helper to print each month stats of a year
};

#endif // CSVREPORTWRITER_H
