#include "Option3Service.h"
#include "MetricGetters.h"
#include <iostream>

// Member initialization for constant members in this case m_stats and m_writer
Option3Service::Option3Service(const StatsCalculator& stats, const ConsoleWriter& writer)
:m_stats(stats), m_writer(writer)
{
}

// Creates an instance of Option3result struct and record calculated stats in result and passes it onto printOption2 with month
// For this, stats are calculated and passed for each month
void Option3Service::executeOption3(const Vector<WeatherRecord>& weatherrecords, int year) const
{
    m_writer.printOption3Header(year);

    for(int month = 1; month <= 12; month++)
    {
        double solarSumRaw = 0.0;

        if(!m_stats.getSum(weatherrecords, year, month, getSolarRadiationValue, solarSumRaw))
        {
            m_writer.printOption3Month(month, false, 0.0);
            continue;
        }

        double totalKWh = solarSumRaw / 6000.0;

        m_writer.printOption3Month(month, true, totalKWh);
    }
}
