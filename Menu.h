#ifndef MENU_H
#define MENU_H

//---------------------------------------------------------------------------------

#include "Vector.h"
#include "Bst.h"
#include <map>
#include <string>
#include "MonthlyData.h"
#include "WeatherRecord.h"
#include "StatsCalculator.h"
#include "ConsoleWriter.h"
#include "CSVReportWriter.h"

//---------------------------------------------------------------------------------

/**
 * @struct SPCCResult
 * @brief Stores the three correlation results for Option 3 (sPCC)
 *
 * Contains the Sample Pearson Correlation Coefficient values
 * for wind vs temperature (S_T), wind vs solar radiation (S_R),
 * and temperature vs solar radiation (T_R).
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 04/04/2026
 */
struct SPCCResult
{
    double s_t;  ///< Correlation between Wind Speed and Temperature
    double s_r;  ///< Correlation between Wind Speed and Solar Radiation
    double t_r;  ///< Correlation between Temperature and Solar Radiation
};

/**
 * @class Menu
 * @brief Handles user interaction and executes weather statistics calculations.
 *
 * Displays menu options, reads user selections, validates input using BST,
 * and performs calculations using aggregated MonthlyData. Implements caching
 * for Option 3 sPCC results using std::map.
 *
 * @author Kyaw Okkar
 * @version 03
 * @date 04/04/2026
 */

class Menu
{
public:
    /**
     * @brief Constructs Menu with aggregated data and validation structures
     * @param monthlyData Primary storage of monthly weather statistics
     * @param rawRecords Raw weather records for MAD calculations
     * @param yearsWithData BST containing all years that have data (for validation)
     * @param monthsWithData BST containing all months that have data (for validation)
     * @param spccCache Map cache for Option 3 sPCC results (key: month, value: SPCCResult)
     */
    Menu(const Vector<MonthlyData>& monthlyData,
         const Vector<WeatherRecord>& rawRecords,
         const Bst<int>& yearsWithData,
         const Bst<int>& monthsWithData,
         std::map<int, SPCCResult>& spccCache);

    /**
     * @brief Main menu loop - displays options and executes user choices
     *
     * Runs continuously until user selects Option 5 (Exit).
     * Validates input and calls appropriate executeOption methods.
     */
    void run();

private:
    const Vector<MonthlyData>& m_monthlyData;      ///< Primary storage of monthly aggregates
    const Vector<WeatherRecord>& m_rawRecords;     ///< Raw data for MAD calculations
    const Bst<int>& m_yearsWithData;               ///< BST for year validation
    const Bst<int>& m_monthsWithData;              ///< BST for month validation
    std::map<int, SPCCResult>& m_spccCache;        ///< Cache for Option 3 results

    StatsCalculator m_stats;      ///< Statistical calculation utility
    ConsoleWriter m_writer;       ///< Console output handler
    CSVReportWriter m_csvWriter;  ///< CSV file output handler

    /**
     * @brief Displays available menu options (1-5)
     */
    void displayOptions() const;

    /**
     * @brief Reads an integer from user input
     * @param prompt Prompt message to display
     * @param outValue Reference to store input value
     * @return true if input is a valid integer, false otherwise
     */
    bool readInt(const char* prompt, int& outValue) const;

    /**
     * @brief Reads and validates selected option (1-5)
     * @param outOption Reference to store option
     * @return true if option is between 1 and 5, false otherwise
     */
    bool readOption(int& outOption) const;

    /**
     * @brief Reads and validates year input (positive integer)
     * @param outYear Reference to store year
     * @return true if year is positive, false otherwise
     */
    bool readYear(int& outYear) const;

    /**
     * @brief Reads and validates month input (1-12)
     * @param outMonth Reference to store month
     * @return true if month is between 1 and 12, false otherwise
     */
    bool readMonth(int& outMonth) const;

    /**
     * @brief Converts month number to month name
     * @param month Month number (1-12)
     * @return Month name string (e.g., "January")
     */
    std::string monthName(int month) const;

    /**
     * @brief Executes Option 1: Wind statistics for a specific month/year
     * @param year Year to query
     * @param month Month to query (1-12)
     */
    void executeOption1(int year, int month);

    /**
     * @brief Executes Option 2: Temperature statistics for all months of a year
     * @param year Year to query
     */
    void executeOption2(int year);

    /**
     * @brief Executes Option 3: sPCC correlations for a month across all years
     * @param month Month to query (1-12)
     */
    void executeOption3(int month);

    /**
     * @brief Executes Option 4: Write monthly statistics to CSV file
     * @param year Year to write data for
     */
    void executeOption4(int year);
};

#endif // MENU_H
