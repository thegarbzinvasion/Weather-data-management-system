#ifndef MONTHLYAGGREGATE_H
#define MONTHLYAGGREGATE_H

/**
 * @struct MonthlyAggregate
 * @brief Temporary aggregation structure for accumulating monthly statistics.
 *
 * Stores sums and sums of squares for wind speed and temperature,
 * sum for solar radiation, and count of readings. Used during Phase 1
 * aggregation before conversion to final MonthlyData.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 03/04/2026
 */

struct MonthlyAggregate
{
    double windSum;      ///< Sum of wind speed readings (m/s)
    double windSqSum;    ///< Sum of squares of wind speed (for std dev)
    double tempSum;      ///< Sum of temperature readings (°C)
    double tempSqSum;    ///< Sum of squares of temperature (for std dev)
    double solarSum;     ///< Sum of solar radiation readings (W/m²)
    int count;           ///< Number of readings in this month

    /**
     * @brief Default constructor - initializes all sums to 0 and count to 0
     */
    MonthlyAggregate()
        : windSum(0), windSqSum(0), tempSum(0), tempSqSum(0), solarSum(0), count(0) {}

    /**
     * @brief Adds a wind speed reading to the aggregate
     * @param speed Wind speed value in m/s
     */
    void addWindSpeed(float speed) {
        windSum += speed;
        windSqSum += speed * speed;
    }

    /**
     * @brief Adds a temperature reading to the aggregate
     * @param temp Temperature value in °C
     */
    void addTemperature(float temp) {
        tempSum += temp;
        tempSqSum += temp * temp;
    }

    /**
     * @brief Adds a solar radiation reading to the aggregate
     * @param solar Solar radiation value in W/m²
     */
    void addSolarRadiation(float solar) {
        solarSum += solar;
    }

    /**
     * @brief Increments the reading count by 1
     */
    void incrementCount() { count++; }
};

#endif // MONTHLYAGGREGATE_H
