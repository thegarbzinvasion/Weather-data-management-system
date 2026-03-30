#include "Option2Service.h"
#include "MetricGetters.h"

// Member initialization for constant members in this case m_stats and m_writer
Option2Service::Option2Service(const StatsCalculator& stats, const ConsoleWriter& writer)
:m_stats(stats), m_writer(writer)
{
}

// Creates an instance of Option2result struct and record calculated stats in result and passes it onto printOption2 with month
// For this, stats are calculated and passed for each month
void Option2Service::executeOption2(const Vector<WeatherRecord>& weatherrecords, int year) const
{
    // Print year header first
    m_writer.printOption2Header(year);

    for(int month = 1; month <= 12; month++)
    {
        double meanRaw = 0.0;
        double stdRaw = 0.0;

        Option2Result result;
        result.meanC = 0.0;
        result.stdDevC = 0.0;

        // Try to compute mean
        if(!m_stats.getMean(weatherrecords, year, month,getAmbientAirTempValue, meanRaw))
        {
            m_writer.printOption2Month(month, false, result);
            continue;
        }

        // Try to compute stdev
        if(!m_stats.getSampleStandardDeviation(weatherrecords, year, month, getAmbientAirTempValue, meanRaw, stdRaw))
        {
            stdRaw = 0.0;   // Rule A fallback
        }

        result.meanC = meanRaw;
        result.stdDevC = stdRaw;

        m_writer.printOption2Month(month, true, result);
    }
}
