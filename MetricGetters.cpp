#include "MetricGetters.h"

// Determines whether an individual record has wind speed value and if so returns the value
bool getWindSpeedValue(const WeatherRecord& weatherrecord, double& outWindSpeed)
{
    if(weatherrecord.hasWindSpeed())
    {
        outWindSpeed = weatherrecord.getWindSpeed();
        return true;
    }
    return false;
}

// Determines whether an individual record has air temp value and if so returns the value
bool getAmbientAirTempValue(const WeatherRecord& weatherrecord, double& outAmbientAirTemp)
{
    if(weatherrecord.hasAmbientAirTemp())
    {
        outAmbientAirTemp = weatherrecord.getAmbientAirTemp();
        return true;
    }
    return false;
}

// Determines whether an individual record has solar radiation value and if so returns the value
bool getSolarRadiationValue(const WeatherRecord& weatherrecord, double& outSolarRadiation)
{
    if(!weatherrecord.hasSolarRadiation())
    {
        return false;
    }

    double value = weatherrecord.getSolarRadiation();

    if(value < 100.0)
    {
        return false;
    }

    outSolarRadiation = value;
    return true;
}

