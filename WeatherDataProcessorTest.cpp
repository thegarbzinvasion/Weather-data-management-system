#include <iostream>
#include <map>
#include "WeatherDataProcessor.h"

using namespace std;

int main()
{
    cout << "=== WeatherDataProcessor Test ===\n\n";

    // Create test map with 2 months
    std::map<string, MonthlyAggregate> tempMap;

    // March 2015 data
    MonthlyAggregate mar;
    mar.windSum = 50.0;
    mar.windSqSum = 500.0;
    mar.tempSum = 150.0;
    mar.tempSqSum = 4500.0;
    mar.solarSum = 10000.0;
    mar.count = 10;
    tempMap["3-2015"] = mar;

    // April 2015 data
    MonthlyAggregate apr;
    apr.windSum = 60.0;
    apr.windSqSum = 600.0;
    apr.tempSum = 160.0;
    apr.tempSqSum = 5000.0;
    apr.solarSum = 12000.0;
    apr.count = 10;
    tempMap["4-2015"] = apr;

    // Convert
    WeatherDataProcessor processor;
    ProcessedData result = processor.convertToVector(tempMap);

    // Display results
    for (int i = 0; i < result.monthlyData.Size(); i++)
    {
        MonthlyData& d = result.monthlyData[i];
        cout << d.month << "/" << d.year << ": "
             << "Wind=" << d.avgWindSpeed
             << ", Temp=" << d.avgTemperature
             << ", Solar=" << d.totalSolarRadiation << endl;
    }

    cout << "\n=== Done ===\n";
    return 0;
}
