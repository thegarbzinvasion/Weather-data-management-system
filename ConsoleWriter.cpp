#include "ConsoleWriter.h"
#include "Option1Service.h"
#include "Option2Service.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

// Converts month number (1-12) to its corresponding month name
std::string ConsoleWriter::MonthName(int month) const
{
    // Static array so it is created only once
    static const char* names[12] = {"January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"};

    // Return empty string if month is invalid
    if(month < 1 || month > 12)
    {
        return "";
    }

    return names[month - 1];
}

// Prints wind statistics for a specific month (Option 1)
void ConsoleWriter::printOption1(int year, int month, bool hasData, const Option1Result& result) const
{
    // If no data exists, print message and exit
    if(!hasData)
    {
        cout << MonthName(month) << " " << year << ": No Data" << endl;
        return;
    }

    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;
    cout << MonthName(month) << " " << year << ":" << endl;

    // Format output to 1 decimal place
    cout << std::fixed << std::setprecision(1);

    cout << "Average speed: " << result.meanKmh << " km/h" << endl;
    cout << "Sample stdev: " << result.stdDevKmh << endl;
}

// Prints header for Option 2 (temperature yearly view)
void ConsoleWriter::printOption2Header(int year) const
{
    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;
    cout << year << endl;
}

// Prints temperature statistics for a specific month (Option 2)
void ConsoleWriter::printOption2Month(int month, bool hasData, const Option2Result& result) const
{
    // If no data exists, print message
    if(!hasData)
    {
        cout << MonthName(month) << ": No Data" << endl;
        return;
    }

    // Format output to 1 decimal place
    cout << std::fixed << std::setprecision(1);
    cout << MonthName(month) << ": average: " << result.meanC
         << " degrees C, stdev: " << result.stdDevC << endl;
}

// Prints header for Option 3 (solar yearly view)
void ConsoleWriter::printOption3Header(int year) const
{
    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;
    cout << year << endl;
}

// Prints total solar radiation for a specific month (Option 3)
void ConsoleWriter::printOption3Month(int month, bool hasData, double totalKWhPerM2) const
{
    // If no solar data exists, print message
    if(!hasData)
    {
        cout << MonthName(month) << ": No Data" << endl;
        return;
    }

    // Format output to 1 decimal place
    cout << std::fixed << std::setprecision(1);
    cout << MonthName(month) << ": " << totalKWhPerM2 << " kWh/m2" << endl;
}
