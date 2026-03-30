#include "StatsCalculator.h"
#include <cmath>

bool StatsCalculator::getMean(const Vector<float> & records, double& outMean) const
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

    outMean = sum / static_cast<double>(records.Size());
    return true;
}

bool StatsCalculator::getSampleStandardDeviation(const Vector<float> & records, double& outStdDev) const
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

bool StatsCalculator::getSum(const Vector<float> & records, double& outSum) const
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

bool getsPCC(const Vector<float> & otherRecords, double& outSpcc) const
{

}

bool getMad(const Vector<float> & records, double& outMeanAbsoluteDeviation) const
{

}
