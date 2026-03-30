#include "Option1Service.h"
#include "MetricGetters.h"

// Member initialization for constant members in this case m_stats and m_writer
Option1Service::Option1Service(const StatsCalculator& stats, const ConsoleWriter& writer)
:m_stats(stats), m_writer(writer)
{
}

// Creates an instance of Option1result struct and record calculated stats in result and passes it onto printOption1 with year and month
void Option1Service::executeOption1(const Vector<WeatherRecord>& weatherrecords, int year, int month)const
{
    double meanRaw = 0;
    double stdRaw = 0;

    Option1Result dummyResult;
    dummyResult.meanKmh = 0.0;
    dummyResult.stdDevKmh = 0.0;

    if(!m_stats.getMean(weatherrecords, year, month, getWindSpeedValue, meanRaw))
    {
        m_writer.printOption1(year, month, false, dummyResult);
        return;
    }

    if(!m_stats.getSampleStandardDeviation(weatherrecords, year, month, getWindSpeedValue, meanRaw, stdRaw))
    {
        stdRaw = 0.0;
    }

    Option1Result result;
    result.meanKmh = meanRaw * 3.6;
    result.stdDevKmh = stdRaw * 3.6;

    m_writer.printOption1(year, month, true, result);
}
