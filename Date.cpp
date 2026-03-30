#include "Date.h"

// Default constructor: Initializes date to the default date of 1/1/2026
Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 2026;
}

// Parameterized constructor: Passes inputs to validation logic
Date::Date(int day, int month, int year)
{
    setDate(day, month, year);
}

// Sets the date based on validation
void Date::setDate(int day, int month, int year)
{
    if(isValidDate(day, month, year))
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
    else
    {
        m_day = 1;
        m_month = 1;
        m_year = 2026;
    }
}

// Validates and checks for leap year instances and invaild dates in general
bool Date::isValidDate(int day, int month, int year) const
{
    if(month < 1 || month > 12 || day < 1 || day > 31 || year < 1)
    {
        return false;
    }

    // Days in each month for non-leap year
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool leap = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
    if (leap && month == 2)
    {
        daysInMonth[1] = 29;
    }

    return day <= daysInMonth[month - 1]; // checking day
}

// Returns the day
int Date::getDay() const
{
    return m_day;
}

// Sets the day directly
void Date::setDay(int day)
{
    if(isValidDate(day, m_month, m_year))
    {
        m_day = day; // Revert if invalid
    }
}

// Returns the month
int Date::getMonth() const
{
    return m_month;
}

// Sets the month directly
void Date::setMonth(int month)
{
    if(isValidDate(m_day, month, m_year))
    {
        m_month = month; // Revert if invalid
    }
}

// Returns the four-digit year
int Date::getYear() const
{
    return m_year;
}

// Sets the year directly
void Date::setYear(int year)
{
    if(isValidDate(m_day, m_month, m_year))
    {
        m_year = year; // Revert if invaild
    }
}

// Compares Date Objs against each other (greater than)
bool Date::operator >(const Date& otherDate) const
{
    if(m_year > otherDate.getYear())
    {
        return true;
    }
    else if(m_year < otherDate.getYear())
    {
        return false;
    }
    if(m_month > otherDate.getMonth())
    {
        return true;
    }
    else if(m_month < otherDate.getMonth())
    {
        return false;
    }

    return m_day > otherDate.getDay();
}

// Compares Date Objs against each other (less than)
bool Date::operator <(const Date& otherDate) const
{
    if(m_year < otherDate.getYear())
    {
        return true;
    }
    else if(m_year > otherDate.getYear())
    {
        return false;
    }
    if(m_month < otherDate.getMonth())
    {
        return true;
    }
    else if(m_month > otherDate.getMonth())
    {
        return false;
    }

    return m_day < otherDate.getDay();
}

// Compares Date Objs against each other (equal to)
bool Date::operator==(const Date& otherDate) const
{
    return m_day == otherDate.getDay() && m_month == otherDate.getMonth() &&
           m_year == otherDate.getYear();
}

// Output operator OUTSIDE of Date class to print out the traversed dates
std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.getDay() << "/" << date.getMonth() << "/" << date.getYear();
    return os;
}
