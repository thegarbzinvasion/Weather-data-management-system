#include "CSVReportWriter.h"
#include "Option4Service.h"
#include <fstream>
#include <iomanip>

// Prints the month name value of a matching integer value representing the month
std::string CSVReportWriter::MonthName(int month) const
{
    // a static local constant, so its not accessible outside the function
    // strictly for this function ONLY.
    static const char* names[12] = {"January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"};

    if(month < 1 || month > 12)
    {
        return "";
    }

    return names[month - 1];
}
// Prints the required format into WindTempSolar.csv
bool CSVReportWriter::writeOption4(const std::string& filename, int year, const Vector<Option4Result>& summaries) const
{
    std::ofstream out(filename.c_str());
    if(!out)
    {
        return false;
    }

    // Write year on first line
    out << year << "\n";

    // If entire year has no data
    if(summaries.IsEmpty())
    {
        out << "No Data\n";
        return true;
    }

    out << std::fixed << std::setprecision(1); // Makes it so that it shows exactly 1 decimal place

    // Each summary is a month row (Option4Service already skipped empty months)
    for(int i = 0; i < summaries.Size(); i++)
    {
        const Option4Result& result = summaries[i];

        out << MonthName(result.month) << ","; // Here a month is printed out for each result's month

        if(result.hasWind)
        {
            out << result.meanWindKmh << "(" << result.stdWindKmh << ")";
        }
        out << ",";

        if(result.hasTemp)
        {
            out << result.meanTempC << "(" << result.stdTempC << ")";
        }
        out << ",";

        if(result.hasSolar)
        {
            out << result.totalSolarKWhPerM2;
        }

        out << "\n";
    }

    return true;
}
