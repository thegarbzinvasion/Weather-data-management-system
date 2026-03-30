#ifndef WEATHERRECORD_H_INCLUDED
#define WEATHERRECORD_H_INCLUDED

//---------------------------------------------------------------------------------

#include "Date.h"
#include "Time.h"

//---------------------------------------------------------------------------------

/**
 * @class WeatherRecord
 * @brief Stores a single weather data record.
 *
 * Contains date, time, and weather metrics such as
 * wind speed, solar radiation, and ambient air temperature.
 * Includes flags to check whether each metric exists.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 15/02/2026
 */

class WeatherRecord
{
public:
    /** @brief Default constructor */
    WeatherRecord();

    /** @brief Sets the date */
    void setDate(const Date& date);

    /** @brief Sets the time */
    void setTime(const Time& time);

    /** @brief Gets the date
        @return const Date& */
    const Date& getDate() const;

    /** @brief Gets the time
        @return const Time& */
    const Time& getTime() const;

    /** @brief Sets wind speed value */
    void setWindSpeed(float windSpeed);

    /** @brief Sets solar radiation value */
    void setSolarRadiation(float solarRadiation);

    /** @brief Sets ambient air temperature */
    void setAmbientAirTemp(float ambientAirTemp);

    /** @brief Gets wind speed
        @return float */
    float getWindSpeed() const;

    /** @brief Gets solar radiation
        @return float */
    float getSolarRadiation() const;

    /** @brief Gets ambient air temperature
        @return float */
    float getAmbientAirTemp() const;

    /** @brief Checks if wind speed exists
        @return bool */
    bool hasWindSpeed() const;

    /** @brief Checks if solar radiation exists
        @return bool */
    bool hasSolarRadiation() const;

    /** @brief Checks if ambient air temperature exists
        @return bool */
    bool hasAmbientAirTemp() const;

private:
    Date m_d;  ///< Date of the record
    Time m_t; ///< Time of the record
    float m_windSpeed; ///< Wind speed value
    float m_solarRadiation; ///< Solar radiation value
    float m_ambientAirTemp; ///< Ambient air temperature value

    bool m_hasWind; ///< True if wind speed exists
    bool m_hasSolar;  ///< True if solar radiation exists
    bool m_hasAirTemp; ///< True if ambient air temperature exists
};

#endif // WEATHERRECORD_H_INCLUDED
