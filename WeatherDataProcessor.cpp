#include "WeatherDataProcessor.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

// Converts a map of MonthlyAggregate to a ProcessedData struct containing Vector<MonthlyData>
ProcessedData WeatherDataProcessor::convertToVector(std::map<std::string, MonthlyAggregate>& tempMap)
{
    ProcessedData result;

    // Iterate through each entry in the map
    for (std::map<std::string, MonthlyAggregate>::iterator it = tempMap.begin(); it != tempMap.end(); ++it)
    {
        const std::string& key = it->first;      // Key format: "Month-Year" (e.g., "3-2015")
        MonthlyAggregate& agg = it->second;      // Aggregated sums and counts

        MonthlyData data;

        // Parse the key to extract month and year
        size_t dashPos = key.find('-');
        if (dashPos != std::string::npos)
        {
            data.month = std::stoi(key.substr(0, dashPos));
            data.year = std::stoi(key.substr(dashPos + 1));

            // Populate BSTs for validation
            result.yearsWithData.InsertTree(data.year);
            result.monthsWithData.InsertTree(data.month);
        }

        // Calculate statistics from aggregated sums
        if (agg.count > 0)
        {
            // Calculate averages (sum / count)
            data.avgWindSpeed = agg.windSum / agg.count;
            data.avgTemperature = agg.tempSum / agg.count;
            data.totalSolarRadiation = agg.solarSum;

            // Calculate standard deviation: sqrt((sum of squares / count) - (mean^2))
            double windVariance = (agg.windSqSum / agg.count) - (data.avgWindSpeed * data.avgWindSpeed);
            data.windStdDev = (windVariance > 0) ? sqrt(windVariance) : 0.0;

            double tempVariance = (agg.tempSqSum / agg.count) - (data.avgTemperature * data.avgTemperature);
            data.tempStdDev = (tempVariance > 0) ? sqrt(tempVariance) : 0.0;
        }

        result.monthlyData.Append(data);
    }

    return result;
}
