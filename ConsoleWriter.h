#ifndef CONSOLEWRITER_H
#define CONSOLEWRITER_H

//---------------------------------------------------------------------------------

#include <string>

//---------------------------------------------------------------------------------

/**
 * @class ConsoleWriter
 * @brief Handles formatted console output for menu options.
 *
 * Prints results for Options 1, 2, and 3
 * in the required format with one decimal place.
 * Contains no calculation logic.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 05/03/2026
 */

/**
* @brief Forward Declaration of Struct by telling Compiler It Exists
*/
struct Option1Result;
struct Option2Result;

class ConsoleWriter
{
public:
    /**
     * @brief Prints results for Option 1
     */
    void printOption1(int year, int month, bool hasData, const Option1Result& result) const;

    /**
     * @brief Prints header for Option 2
     */
    void printOption2Header(int year) const;

    /**
     * @brief Prints monthly result for Option 2
     */
    void printOption2Month(int month, bool hasData, const Option2Result& result) const;

    /**
     * @brief Prints header for Option 3
     */
    void printOption3Header(int year) const;

    /**
     * @brief Prints monthly result for Option 3
     */
    void printOption3Month(int month, bool hasData, double totalKWhPerM2) const;

private:
    /**
     * @brief Converts month number to month name
     * @return std::string */
    std::string MonthName(int month) const; // private helper to print each month stats of a year
};
#endif // CONSOLEWRITER_H
