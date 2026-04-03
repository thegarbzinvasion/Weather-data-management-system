#include "Option4Service.h"
#include "MetricGetters.h"

// Member initialization for constant members in this case m_stats and m_writer
Option4Service::Option4Service(const StatsCalculator& stats, const CSVReportWriter& writer)
:m_stats(stats), m_writer(writer)
{
}

// Private helper method for executeOption4()
template<typename GetterFunc>
bool Option4Service::calculateStats(const Vector<WeatherRecord>& records,
                                   int year,
                                   int month,
                                   GetterFunc getter,
                                   double& mean,
                                   double& stdDev) const
{
    if (!m_stats.getMean(records, year, month, getter, mean))
    {
        return false;  // No data available
    }

    if (!m_stats.getSampleStandardDeviation(records, year, month, getter, mean, stdDev))
    {
        stdDev = 0.0;  // Not enough data for std dev
    }

    return true;
}

// For a given year, calculates monthly statistics (wind, temperature, solar)
// and writes the results to the specified output file.
void Option4Service::executeOption4(const Vector<WeatherRecord>& weatherrecords, int year, const std::string& outFile) const
{
    Vector<Option4Result> summaries;

    for(int month = 1; month <= 12; month++)
    {
        Option4Result result;
        result.month = month;

        double windMeanMs = 0.0, windStdMs = 0.0;
        if (calculateStats(weatherrecords, year, month, getWindSpeedValue, windMeanMs, windStdMs))
        {
            result.hasWind = true;
            result.meanWindKmh = windMeanMs * 3.6;
            result.stdWindKmh = windStdMs * 3.6;
        }

        // Temperature - using the helper method
        double tempMeanC = 0.0, tempStdC = 0.0;
        if (calculateStats(weatherrecords, year, month, getAmbientAirTempValue, tempMeanC, tempStdC))
        {
            result.hasTemp = true;
            result.meanTempC = tempMeanC;
            result.stdTempC = tempStdC;
        }

        // Solar - different logic (uses sum), so keep as is
        double solarSumRaw = 0.0;
        if (m_stats.getSum(weatherrecords, year, month, getSolarRadiationValue, solarSumRaw))
        {
            result.hasSolar = true;
            result.totalSolarKWhPerM2 = solarSumRaw / 6000.0;
        }

        if(result.hasWind || result.hasTemp || result.hasSolar)
        {
            summaries.Append(result);
        }
    }

    m_writer.writeOption4(outFile, year, summaries);
}
