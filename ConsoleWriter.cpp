#include "ConsoleWriter.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

// Prints a visual separator line for better output formatting
void ConsoleWriter::printSeparator() const
{
    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;
}

// Converts month number (1-12) to full month name
std::string ConsoleWriter::monthName(int month) const
{
    static const char* names[12] = {"January", "February", "March", "April", "May", "June",
                                    "July", "August", "September", "October", "November", "December"};
    if (month < 1 || month > 12) return "";
    return names[month - 1];
}

// Prints wind statistics for Option 1 - shows average speed and standard deviation in km/h
void ConsoleWriter::printOption1(int year, int month, bool hasData, double meanKmh, double stdDevKmh) const
{
    if (!hasData)
    {
        cout << monthName(month) << " " << year << ": No Data" << endl;
        return;
    }

    printSeparator();
    cout << monthName(month) << " " << year << ":" << endl;
    cout << fixed << setprecision(1);
    cout << "Average speed: " << meanKmh << " km/h" << endl;
    cout << "Sample stdev: " << stdDevKmh << endl;
}

// Prints the header (year) for Option 2 temperature view
void ConsoleWriter::printOption2Header(int year) const
{
    printSeparator();
    cout << year << endl;
}

// Prints temperature statistics for a single month in Option 2
void ConsoleWriter::printOption2Month(int month, bool hasData, double meanC, double stdDevC) const
{
    if (!hasData)
    {
        cout << monthName(month) << ": No Data" << endl;
        return;
    }

    cout << fixed << setprecision(1);
    cout << monthName(month) << ": average: " << meanC << " degrees C, stdev: " << stdDevC << endl;
}

// Prints sPCC correlation results for Option 3 - shows S_T, S_R, T_R values
void ConsoleWriter::printOption3Result(int month, double s_t, double s_r, double t_r) const
{
    printSeparator();
    cout << "Sample Pearson Correlation Coefficient for " << monthName(month) << endl;
    cout << fixed << setprecision(2);
    cout << "S_T: " << s_t << endl;
    cout << "S_R: " << s_r << endl;
    cout << "T_R: " << t_r << endl;
}
