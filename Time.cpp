#include "Time.h"
#include <stdexcept>

// Sets time to 00:00
Time::Time()
{
    m_hour = 0;
    m_minute = 0;
}

// sets hour and minute using validation
Time::Time(int hour, int minute)
{
    setHour(hour);
    setMinute(minute);
}

// Sets the hour (valid range: 0�23)
void Time::setHour(int hour)
{
    if(hour >= 0 && hour <= 23)
    {
        m_hour = hour;
    }
    else
    {
        throw std::invalid_argument("Invalid hour");
    }
}

// Sets the minute (valid range: 0�59)
void Time::setMinute(int minute)
{
    if(minute >= 0 && minute <= 59)
    {
        m_minute = minute;
    }
    else
    {
        throw std::invalid_argument("Invalid minute");
    }
}

// Returns the hour
int Time::getHour() const
{
    return m_hour;
}

// Returns the minute
int Time::getMinute() const
{
    return m_minute;
}
