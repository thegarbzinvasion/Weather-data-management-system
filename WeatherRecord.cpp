#include "WeatherRecord.h"

// Initialise all values to 0 and flags to false
WeatherRecord::WeatherRecord()
{
    m_windSpeed = 0.0f;
    m_solarRadiation = 0.0f;
    m_ambientAirTemp = 0.0f;
    m_hasWind = false;
    m_hasSolar = false;
    m_hasAirTemp = false;
}

// Sets the date of the record
void WeatherRecord::setDate(const Date& date)
{
    m_d = date;
}

// Sets the time of the record
void WeatherRecord::setTime(const Time& time)
{
    m_t = time;
}

// Returns the date
const Date& WeatherRecord::getDate() const
{
    return m_d;
}

// Returns the time
const Time& WeatherRecord::getTime() const
{
    return m_t;
}

// Sets wind speed and marks wind as available
void WeatherRecord::setWindSpeed(float windSpeed)
{
    m_windSpeed = windSpeed;
    m_hasWind = true;
}

// Sets solar radiation and marks solar as available
void WeatherRecord::setSolarRadiation(float solarRadiation)
{
    m_solarRadiation = solarRadiation;
    m_hasSolar = true;
}

// Sets ambient air temperature and marks temperature as available
void WeatherRecord::setAmbientAirTemp(float ambientAirTemp)
{
    m_ambientAirTemp = ambientAirTemp;
    m_hasAirTemp = true;
}

// Returns wind speed
float WeatherRecord::getWindSpeed() const
{
    return m_windSpeed;
}

// Returns solar radiation
float WeatherRecord::getSolarRadiation() const
{
    return m_solarRadiation;
}

// Returns ambient air temperature
float WeatherRecord::getAmbientAirTemp() const
{
    return m_ambientAirTemp;
}

// Returns true if wind speed exists
bool WeatherRecord::hasWindSpeed() const
{
    return m_hasWind;
}

// Returns true if solar radiation exists
bool WeatherRecord::hasSolarRadiation() const
{
    return m_hasSolar;
}

// Returns true if ambient air temperature exists
bool WeatherRecord::hasAmbientAirTemp() const
{
    return m_hasAirTemp;
}
