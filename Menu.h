#ifndef MENU_H
#define MENU_H

/**
 * @class Menu
 * @brief Handles user interaction and input validation.
 *
 * Displays menu options, reads user selections,
 * and gathers required input such as year and month.
 * Does not perform calculations.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 17/03/2026
 */

struct Request
{
    int option; ///< Selected menu option (1�5)
    int year; ///< Year input (used for options 1�4)
    int month; ///< Month input (used for option 1 only, otherwise 0)
};

class Menu
{
public:
    /**
     * @brief Collects user request (option, year, month)
     * @return Request Struct containing user input
     */
    Request getRequest() const;
private:
    /**
     * @brief Displays available menu options
     */
    void displayOptions() const;
    /**
     * @brief Reads an integer from user input
     * @return bool True if input valid
     */
    bool readInt(const char* prompt, int& outValue) const;

    /**
     * @brief Reads selected option
     * @return bool True if option valid
     */
    bool readOption(int& outOption) const;
    /**
     * @brief Reads year input
     * @return bool True if year valid
     */
    bool readYear(int& outYear) const;
    /**
     * @brief Reads month input
     * @return bool True if month valid
     */
    bool readMonth(int& outMonth) const;
};

#endif // MENU_H
