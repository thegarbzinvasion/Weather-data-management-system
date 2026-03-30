#ifndef STATSCALCULATOR_H
#define STATSCALCULATOR_H

//---------------------------------------------------------------------------------

#include "Vector.h"
#include "WeatherRecord.h"

//---------------------------------------------------------------------------------

/**
 * @class StatsCalculator
 * @brief Performs statistical calculations on WeatherRecord data.
 *
 * Calculates mean, sample standard deviation, and sum
 * using a function pointer to extract metric values.
 * Filters data by year and month.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 24/02/2026
 */

class StatsCalculator
{
public:
    /**
     * @brief Function pointer type for extracting metric values
     */
    typedef bool (*valueGetter)(const WeatherRecord& record, double& outValue);

    /**
     * @brief Calculates mean value
     * @return bool True if data exists
     */
    bool getMean(const Vector<float> & records, double& outMean) const;

    /**
     * @brief Calculates sample standard deviation
     * @return bool True if data exists
     */
    bool getSampleStandardDeviation(const Vector<float> & records, double& outStdDev) const;

    /**
     * @brief Calculates sum of values
     * @return bool True if data exists
     */
    bool getSum(const Vector<float> & records, double& outSum) const;

    /**
     * @brief Calculates spCC that calculates the sample PCC between two numeric vectors
     * @return bool True if calculation is successful
     */
    bool getsPCC(const Vector<float> & otherRecords, double& outSpcc) const;


    /**
     * @brief Calculates the mean absolute deviation of the numerical vector
     * @return bool True if calculation is successful
     */
    bool getMad(const Vector<float> & records, double& outMeanAbsoluteDeviation) const;
};

#endif // STATSCALCULATOR_H
