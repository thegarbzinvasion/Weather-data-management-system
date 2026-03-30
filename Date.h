#ifndef DATE_H
#define DATE_H

//---------------------------------------------------------------------------------

#include <iostream>

//---------------------------------------------------------------------------------

/**
 * @class Date
 * @brief Represents a calendar date (Day, Month, Year).
 * * Uses standard C time structures to validate dates and provide
 * localized month names via put_time.
 * * Month names are handled by the system to support multiple languages.\n
 * Years are stored as four digits.\n
 * * @author Kyaw Okkar, Gemini, w3Schools
 * @version 01
 * @date 30/01/2026 Kyaw Okkar, Gemini, w3Schools, Started, created get/set methods,
 * added ctime operations for the conversion of nums to months and initalization
 *
 * @date 14/01/2026 Kyaw Okkar
 * Added comparison overloaded operators to accommodate for BST
 */

class Date
{
public:
    /** @brief Default constructor. Sets day, month, and year to 1/1/2026 */
    Date();

    /** @brief Parameterized constructor. Validates on entry. */
    Date(int day, int month, int year);

    /** @brief Validates and sets the date. Falls back to default if invalid. */
    void setDate(int day, int month, int year);

    /** @brief Sets day
    @param day
    @return void */
    void setDay(int day);

    /** @brief Sets month
    @param month
    @return void */
    void setMonth(int month);
    void setYear(int year);

    /** @brief Gets day
    @return int */
    int getDay() const;

    /** @brief
    Gets month (1-12)
    @return int */
    int getMonth() const;

    /** @brief Gets year
    @return int */
    int getYear() const;

    /** @brief Compares dates
    @param otherDate
    @return bool */
    bool operator >(const Date& otherDate) const;
    bool operator <(const Date& otherDate) const;
    bool operator==(const Date& otherDate) const;

private:
    int m_day; ///< Day of the month
    int m_month; ///< Month of the year (1-12)
    int m_year; ///< Four-digit year

    bool isValidDate(int day, int month, int year) const; ///< Private helper method for validation of date
};

/** @brief Outputs dates
    @param Date
    @return formatted output sequence (DD/MM/YYYY) */
std::ostream& operator<<(std::ostream& os, const Date& date);

#endif // DATE_H
