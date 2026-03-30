#ifndef TIME_H
#define TIME_H

/**
 * @class Time
 * @brief Represents a calendar date (Day, Month, Year).
 * * Uses standard C time structures to validate dates and provide
 * localized month names via put_time.
 * * Month names are handled by the system to support multiple languages.\n
 * Years are stored as four digits.\n
 * * @author Kyaw Okkar, Gemini, w3Schools
 * @version 01
 * @date 17/02/2026 Kyaw Okkar,
 * created get/set methods,
 * added ctime operations for the conversion of nums to months and initalization
 *
 */

class Time
{
public:
    /** @brief Default constructor */
    Time();

    /**
     * @brief Parameterized constructor
     */
    Time(int hour, int minute);

    /**
     * @brief Sets the hour value
     */
    void setHour(int hour);

    /**
     * @brief Sets the minute value
     */
    void setMinute(int minute);

    /**
     * @brief Gets hour
     * @return int
     */
    int getHour() const;

    /**
     * @brief Gets minute
     * @return int
     */
    int getMinute() const;

private:
    int m_hour; ///< Hour value (0�23)
    int m_minute; ///< Minute value (0�59)
};


#endif // TIME_H
