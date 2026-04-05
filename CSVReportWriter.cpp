#include "CSVReportWriter.h"
#include "StatsCalculator.h"
#include "WeatherRecord.h"
#include "MonthlyData.h"
#include <fstream>
#include <iomanip>
#include <cmath>

// Implementation of monthName - converts month number to name
std::string CSVReportWriter::monthName(int month) const
{
    static const char* names[12] = {"January", "February", "March", "April", "May", "June",
                                    "July", "August", "September", "October", "November", "December"};
    if (month < 1 || month > 12) return "";
    return names[month - 1];
}

// Implementation of writeOption4 - writes monthly statistics to CSV file
bool CSVReportWriter::writeOption4(const std::string& filename,
                                    int year,
                                    const Vector<MonthlyData>& monthlyData,
                                    const Vector<WeatherRecord>& rawRecords) const
{
    std::ofstream outFile(filename);
    if (!outFile) return false;

    outFile << year << std::endl;

    // Filter data for the specified year
    Vector<MonthlyData> yearData;
    for (int i = 0; i < monthlyData.Size(); i++)
    {
        if (monthlyData[i].year == year)
        {
            yearData.Append(monthlyData[i]);
        }
    }

    // If no data for this year, write "No Data" and exit
    if (yearData.IsEmpty())
    {
        outFile << "No Data" << std::endl;
        outFile.close();
        return true;
    }

    StatsCalculator stats;
    outFile << std::fixed << std::setprecision(1);

    // Loop through each month and write its statistics
    for (int i = 0; i < yearData.Size(); i++)
    {
        const MonthlyData& data = yearData[i];

        // Collect raw readings for MAD calculation
        Vector<double> windReadings;
        Vector<double> tempReadings;

        for (int j = 0; j < rawRecords.Size(); j++)
        {
            const WeatherRecord& record = rawRecords[j];
            if (record.getDate().getYear() == data.year &&
                record.getDate().getMonth() == data.month)
            {
                if (record.hasWindSpeed())
                {
                    windReadings.Append(record.getWindSpeed());
                }
                if (record.hasAmbientAirTemp())
                {
                    tempReadings.Append(record.getAmbientAirTemp());
                }
            }
        }

        // Calculate MAD for wind
        double windMAD = 0.0;
        if (windReadings.Size() > 0)
        {
            stats.getMad(windReadings, windMAD);
        }

        // Calculate MAD for temperature
        double tempMAD = 0.0;
        if (tempReadings.Size() > 0)
        {
            stats.getMad(tempReadings, tempMAD);
        }

        // Write output in CSV format: Month, Wind(stdev,MAD), Temp(stdev,MAD), Solar
        outFile << monthName(data.month) << ",";
        outFile << data.avgWindSpeed * 3.6 << "(" << data.windStdDev * 3.6 << "," << windMAD << ")";
        outFile << ",";
        outFile << data.avgTemperature << "(" << data.tempStdDev << "," << tempMAD << ")";
        outFile << ",";
        outFile << data.totalSolarRadiation / 6000.0;
        outFile << "\n";
    }

    outFile.close();
    return true;
}
