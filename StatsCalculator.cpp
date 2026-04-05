#include "StatsCalculator.h"
#include <cmath>

// Calculates the arithmetic mean (average) of a vector of doubles
bool StatsCalculator::getMean(const Vector<double>& records, double& outMean) const
{
    if (records.Size() == 0)
    {
        return false;
    }

    double sum = 0;
    for (int i = 0; i < records.Size(); i++)
    {
        sum += records[i];
    }

    outMean = sum / records.Size();
    return true;
}

// Calculates sample standard deviation (uses n-1 formula)
bool StatsCalculator::getSampleStandardDeviation(const Vector<double>& records,
                                                  double mean,
                                                  double& outStdDev) const
{
    int n = records.Size();
    if (n < 2)  // Need at least 2 values for sample standard deviation
    {
        return false;
    }

    double sumSq = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double diff = records[i] - mean;
        sumSq += diff * diff;
    }

    outStdDev = std::sqrt(sumSq / static_cast<double>(n - 1));
    return true;
}

// Calculates the sum of all values in a vector
bool StatsCalculator::getSum(const Vector<double>& records, double& outSum) const
{
    if (records.Size() == 0)
    {
        return false;
    }

    double sum = 0;
    for (int i = 0; i < records.Size(); ++i)
    {
        sum += records[i];
    }

    outSum = sum;
    return true;
}

// Calculates the Sample Pearson Correlation Coefficient (sPCC) between two vectors
bool StatsCalculator::getsPCC(const Vector<double>& thisRecords,
                               const Vector<double>& otherRecords,
                               double& outSpcc) const
{
    // Check for empty vectors
    if (thisRecords.Size() == 0 || otherRecords.Size() == 0)
    {
        return false;
    }

    // Check vectors have same size
    if (thisRecords.Size() != otherRecords.Size())
    {
        return false;
    }

    int n = thisRecords.Size();

    // Need at least 2 pairs for correlation
    if (n < 2)
    {
        return false;
    }

    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;
    double sumY2 = 0;

    // Calculate sums needed for correlation formula
    for (int i = 0; i < n; ++i)
    {
        sumX += thisRecords[i];
        sumY += otherRecords[i];
        sumXY += thisRecords[i] * otherRecords[i];
        sumX2 += thisRecords[i] * thisRecords[i];
        sumY2 += otherRecords[i] * otherRecords[i];
    }

    double numerator = n * sumXY - sumX * sumY;
    double denominator = std::sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

    if (denominator == 0)
    {
        return false;
    }

    outSpcc = numerator / denominator;
    return true;
}

// Calculates the Mean Absolute Deviation (MAD) of a vector
bool StatsCalculator::getMad(const Vector<double>& records, double& outMeanAbsoluteDeviation) const
{
    if (records.Size() == 0)
    {
        return false;
    }

    double mean;
    if (!getMean(records, mean))  // First calculate the mean
    {
        return false;
    }

    int n = records.Size();
    double sumAbsoluteDeviations = 0;

    // Sum the absolute differences from the mean
    for (int i = 0; i < n; ++i)
    {
        sumAbsoluteDeviations += std::abs(records[i] - mean);
    }

    outMeanAbsoluteDeviation = sumAbsoluteDeviations / n;
    return true;
}
