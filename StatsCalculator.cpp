#include "StatsCalculator.h"

bool StatsCalculator::getSampleStandardDeviation(const Vector<float>& records, double& outStdDev) const
{
    int n = records.Size();
    if (n < 2)
    {
        return false;
    }

    double sumSq = 0.0;
    for(int i = 0; i < n; ++i)
    {
        double diff = records[i] - mean;
        sumSq += diff * diff;
    }

    outStdDev = std::sqrt(sumSq / static_cast<double>(n - 1));
    return true;
}

bool StatsCalculator::getSum(const Vector<float>& records, double& outSum) const
{
    if(records.Size() == 0)
    {
        return false;
    }

    double sum = 0;

    for(int i = 0; i < records.Size(); ++i)
    {
        sum += records[i];
    }

    outSum = sum;
    return true;
}

bool getsPCC(const Vector<float>& thisRecords, const Vector<float>& otherRecords, double& outSpcc) const
{
    if(thisRecords.Size() || otherRecords.Size() == 0)
    {
        return false;
    }

    if(thisRecords.Size() != otherRecords.Size())
    {
        return false;
    }

    int n = thisRecords.Size();

    double sumX = 0;
    double sumY = 0;

    for(int i = 0; i < n; ++i)
    {
        sumX += thisRecords[i];
        sumY += otherRecords[i];
    }

    double meanX = sumX / n;
    double meanY = sumY / n;

    double numerator = 0;

    double sumSqX = 0;
    double sumSqY = 0;

    for(int i = 0; i < n; ++i)
    {
        double diffX = thisRecords[i] - meanX;
        double diffY = otherRecords[i] - meanY;

        numerator += diffX * diffY;
        sumSqX += diffX * diffX;
        sumSqY += diffY * diffY;
    }

    double denominator = sqrt(sumSqX) * sqrt(sumSqY);

    if(denomimator == 0)
    {
        return false;
    }

    outPcc = numerator / denominator;
    return true;
}

bool getMad(const Vector<float>& records, double& outMeanAbsoluteDeviation) const
{
    if(records.Size() == 0)
    {
        return false;
    }

    int n = records.Size();

    double mean;
    if(!getMean(record, mean))
    {
        return false;
    }

    double sumAbsoluteDeviations = 0;
    for(int i = 0; i < n; ++i)
    {
        sumAbsoluteDeviations += abs(records[i] = mean);
    }

    outMeanAbsoluteDeviation = sumAbsoluteDeviations / n;
    return true;
}
