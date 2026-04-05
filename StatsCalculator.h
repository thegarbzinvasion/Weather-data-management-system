#ifndef STATSCALCULATOR_H
#define STATSCALCULATOR_H

//---------------------------------------------------------------------------------

#include "Vector.h"

//---------------------------------------------------------------------------------

/**
 * @class StatsCalculator
 * @brief Performs statistical calculations on numeric vectors.
 *
 * Calculates mean, sample standard deviation, sum, Pearson correlation
 * coefficient (sPCC), and mean absolute deviation (MAD) for Vector<double>.
 *
 * @author Kyaw Okkar
 * @version 02
 * @date 03/04/2026
 */

class StatsCalculator
{
public:
    /**
     * @brief Calculates the arithmetic mean of a vector
     * @param records Vector of numeric values
     * @param outMean Reference to store the calculated mean
     * @return true if vector is non-empty, false otherwise
     */
    bool getMean(const Vector<double>& records, double& outMean) const;

    /**
     * @brief Calculates the sample standard deviation of a vector
     * @param records Vector of numeric values
     * @param mean Pre-calculated mean of the vector
     * @param outStdDev Reference to store the calculated standard deviation
     * @return true if vector has at least 2 elements, false otherwise
     */
    bool getSampleStandardDeviation(const Vector<double>& records, double mean, double& outStdDev) const;

    /**
     * @brief Calculates the sum of all values in a vector
     * @param records Vector of numeric values
     * @param outSum Reference to store the calculated sum
     * @return true if vector is non-empty, false otherwise
     */
    bool getSum(const Vector<double>& records, double& outSum) const;

    /**
     * @brief Calculates the Sample Pearson Correlation Coefficient (sPCC) between two vectors
     * @param thisRecords First vector of numeric values
     * @param otherRecords Second vector of numeric values
     * @param outSpcc Reference to store the correlation coefficient (-1 to +1)
     * @return true if vectors have at least 2 elements and equal size, false otherwise
     */
    bool getsPCC(const Vector<double>& thisRecords, const Vector<double>& otherRecords, double& outSpcc) const;

    /**
     * @brief Calculates the Mean Absolute Deviation (MAD) of a vector
     * @param records Vector of numeric values
     * @param outMeanAbsoluteDeviation Reference to store the calculated MAD
     * @return true if vector is non-empty, false otherwise
     */
    bool getMad(const Vector<double>& records, double& outMeanAbsoluteDeviation) const;
};

#endif // STATSCALCULATOR_H
