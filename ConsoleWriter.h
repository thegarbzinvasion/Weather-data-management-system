#ifndef CONSOLEWRITER_H
#define CONSOLEWRITER_H

//---------------------------------------------------------------------------------

#include <string>

//---------------------------------------------------------------------------------

/**
 * @class ConsoleWriter
 * @brief Handles formatted console output for weather statistics.
 *
 * Provides methods to print wind stats, temperature stats,
 * and sPCC results to the console with proper formatting.
 *
 * @author Kyaw Okkar
 * @version 02
 * @date 01/04/2026
 */

class ConsoleWriter
{
public:
    /**
     * @brief Prints wind statistics for a specific month/year (Option 1)
     * @param year Year of the data
     * @param month Month number (1-12)
     * @param hasData True if data exists for this month/year
     * @param meanKmh Average wind speed in km/h
     * @param stdDevKmh Standard deviation of wind speed in km/h
     */
    void printOption1(int year, int month, bool hasData, double meanKmh, double stdDevKmh) const;

    /**
     * @brief Prints header for yearly temperature view (Option 2)
     * @param year Year being displayed
     */
    void printOption2Header(int year) const;

    /**
     * @brief Prints temperature statistics for a specific month (Option 2)
     * @param month Month number (1-12)
     * @param hasData True if data exists for this month
     * @param meanC Average temperature in Celsius
     * @param stdDevC Standard deviation of temperature in Celsius
     */
    void printOption2Month(int month, bool hasData, double meanC, double stdDevC) const;

    /**
     * @brief Prints sPCC results for a specific month (Option 3)
     * @param month Month number (1-12)
     * @param s_t Correlation between wind speed and temperature
     * @param s_r Correlation between wind speed and solar radiation
     * @param t_r Correlation between temperature and solar radiation
     */
    void printOption3Result(int month, double s_t, double s_r, double t_r) const;

    /**
     * @brief Converts month number to month name
     * @param month Month number (1-12)
     * @return Month name string
     */
    std::string monthName(int month) const;

private:
    /**
     * @brief Prints separator line for visual formatting
     */
    void printSeparator() const;
};

#endif // CONSOLEWRITER_H
