#ifndef METRICGETTERS_H
#define METRICGETTERS_H

//---------------------------------------------------------------------------------

#include "WeatherRecord.h"

//---------------------------------------------------------------------------------

/**
 * @file MetricGetters.h
 * @brief Provides helper functions to extract metric values from WeatherRecord.
 *
 * Each function checks whether the requested metric exists
 * before returning the value. Used by StatsCalculator.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 20/02/2026
 */

/** @brief Extracts wind speed value
    @return bool True if value exists */
bool getWindSpeedValue(const WeatherRecord& weatherrecord, double& outWindSpeed);

/** @brief Extracts ambient air temperature value
    @return bool True if value exists */
bool getAmbientAirTempValue(const WeatherRecord& weatherrecord, double& outAmbientAirTemp);

/** @brief Extracts solar radiation value
    @return bool True if value exists */
bool getSolarRadiationValue(const WeatherRecord& weatherrecord, double& outSolarRadiation);

#endif // METRICGETTERS_H
