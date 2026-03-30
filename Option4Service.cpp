#include "Option4Service.h"
#include "MetricGetters.h"

// Member initialization for constant members in this case m_stats and m_writer
Option4Service::Option4Service(const StatsCalculator& stats, const CSVReportWriter& writer)
:m_stats(stats), m_writer(writer)
{
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

        result.hasWind = false;
        result.meanWindKmh = 0.0;
        result.stdWindKmh = 0.0;

        result.hasTemp = false;
        result.meanTempC = 0.0;
        result.stdTempC = 0.0;

        result.hasSolar = false;
        result.totalSolarKWhPerM2 = 0.0;

        double windMeanMs = 0.0;
        double windStdMs = 0.0;

        if(m_stats.getMean(weatherrecords, year, month, getWindSpeedValue, windMeanMs))
        {
            result.hasWind = true;

            if(!m_stats.getSampleStandardDeviation(weatherrecords, year, month, getWindSpeedValue, windMeanMs, windStdMs))
            {
                windStdMs = 0.0;
            }

            result.meanWindKmh = windMeanMs * 3.6;
            result.stdWindKmh = windStdMs * 3.6;
        }

        double tempMeanC = 0.0;
        double tempStdC = 0.0;

        if(m_stats.getMean(weatherrecords, year, month, getAmbientAirTempValue, tempMeanC))
        {
            result.hasTemp = true;

            if(!m_stats.getSampleStandardDeviation(weatherrecords, year, month, getAmbientAirTempValue, tempMeanC, tempStdC))
            {
                tempStdC = 0.0;
            }

            result.meanTempC = tempMeanC;
            result.stdTempC = tempStdC;
        }

        double solarSumRaw = 0.0;

        if(m_stats.getSum(weatherrecords, year, month, getSolarRadiationValue, solarSumRaw))
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
