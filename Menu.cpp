#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;

Menu::Menu(const Vector<MonthlyData>& monthlyData,
           const Vector<WeatherRecord>& rawRecords,
           const Bst<int>& yearsWithData,
           const Bst<int>& monthsWithData,
           std::map<int, SPCCResult>& spccCache)
    : m_monthlyData(monthlyData)
    , m_rawRecords(rawRecords)
    , m_yearsWithData(yearsWithData)
    , m_monthsWithData(monthsWithData)
    , m_spccCache(spccCache)
{
}

void Menu::displayOptions() const
{
    cout << endl;
    cout << "===================================================================" << endl;
    cout << "                                                                   " << endl;
    cout << "                   WEATHER RECORD SERVICES                         " << endl;
    cout << "                                                                   " << endl;
    cout << "===================================================================" << endl;
    cout << "1. Average wind speed and sample standard deviation (specified month/year)" << endl;
    cout << "2. Average temperature and sample standard deviation (each month of a specified year)" << endl;
    cout << "3. Sample Pearson Correlation Coefficient (sPCC) (for a month across all years)" << endl;
    cout << "4. Write monthly statistics to CSV file (wind speed(stdev, mad), temperature(stdev, mad), solar radiation)" << endl;
    cout << "5. Exit                                                        " << endl;
    cout << "===================================================================" << endl;
    cout << endl;
}

bool Menu::readInt(const char* prompt, int& outValue) const
{
    cout << prompt;
    if (!(cin >> outValue))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    cin.ignore(10000, '\n');
    return true;
}

bool Menu::readOption(int& outOption) const
{
    int opt;
    if (!readInt("Enter a VALID option (1-5): ", opt)) return false;
    if (opt < 1 || opt > 5) return false;
    outOption = opt;
    return true;
}

bool Menu::readYear(int& outYear) const
{
    int year;
    if (!readInt("Enter a VALID year: ", year)) return false;
    if (year <= 0) return false;
    outYear = year;
    return true;
}

bool Menu::readMonth(int& outMonth) const
{
    int month;
    if (!readInt("Enter a VALID month (1-12): ", month)) return false;
    if (month < 1 || month > 12) return false;
    outMonth = month;
    return true;
}

std::string Menu::monthName(int month) const
{
    static const char* names[12] = {"January", "February", "March", "April", "May", "June",
                                    "July", "August", "September", "October", "November", "December"};
    if (month < 1 || month > 12) return "";
    return names[month - 1];
}

// Option 1: Using ConsoleWriter
void Menu::executeOption1(int year, int month)
{
    // Check BST for existence
    if (!m_yearsWithData.SearchTree(year) || !m_monthsWithData.SearchTree(month))
    {
        m_writer.printOption1(year, month, false, 0.0, 0.0);
        return;
    }

    // Search Vector for data
    for (int i = 0; i < m_monthlyData.Size(); i++)
    {
        const MonthlyData& data = m_monthlyData[i];
        if (data.year == year && data.month == month)
        {
            double meanKmh = data.avgWindSpeed * 3.6;
            double stdDevKmh = data.windStdDev * 3.6;
            m_writer.printOption1(year, month, true, meanKmh, stdDevKmh);
            return;
        }
    }

    m_writer.printOption1(year, month, false, 0.0, 0.0);
}

// Option 2: Using ConsoleWriter
void Menu::executeOption2(int year)
{
    // Check BST for existence
    if (!m_yearsWithData.SearchTree(year))
    {
        m_writer.printOption2Header(year);
        for (int month = 1; month <= 12; month++)
        {
            m_writer.printOption2Month(month, false, 0.0, 0.0);
        }
        return;
    }

    m_writer.printOption2Header(year);

    for (int month = 1; month <= 12; month++)
    {
        bool found = false;
        for (int i = 0; i < m_monthlyData.Size(); i++)
        {
            const MonthlyData& data = m_monthlyData[i];
            if (data.year == year && data.month == month)
            {
                m_writer.printOption2Month(month, true, data.avgTemperature, data.tempStdDev);
                found = true;
                break;
            }
        }
        if (!found)
        {
            m_writer.printOption2Month(month, false, 0.0, 0.0);
        }
    }
}

// Option 3: Using StatsCalculator for sPCC + Map Cache
void Menu::executeOption3(int month)
{
    // Check BST for existence
    if (!m_monthsWithData.SearchTree(month))
    {
        cout << "No data for month " << month << endl;
        return;
    }

    // Check Map cache
    if (m_spccCache.find(month) != m_spccCache.end())
    {
        SPCCResult cached = m_spccCache.at(month);
        m_writer.printOption3Result(month, cached.s_t, cached.s_r, cached.t_r);
        return;
    }

    // Collect data for this month across all years
    Vector<double> windSpeeds;
    Vector<double> temperatures;
    Vector<double> solarRadiation;

    for (int i = 0; i < m_monthlyData.Size(); i++)
    {
        const MonthlyData& data = m_monthlyData[i];
        if (data.month == month)
        {
            windSpeeds.Append(data.avgWindSpeed);
            temperatures.Append(data.avgTemperature);

            double solarSum = 0;
            int solarCount = 0;

            for(int j = 0; j < m_rawRecords.Size(); j++)
            {
                const WeatherRecord& record = m_rawRecords[j];
                if (record.getDate().getYear() == data.year &&
                    record.getDate().getMonth() == data.month &&
                    record.hasSolarRadiation())
                {
                    solarSum += record.getSolarRadiation();
                    solarCount++;
                }
            }

            double avgSolarWm2 = (solarCount > 0) ? solarSum / solarCount : 0;
            solarRadiation.Append(avgSolarWm2);
        }
    }

    // Check if enough data points for correlation
    if (windSpeeds.Size() < 2)
    {
        cout << "Insufficient data for month " << month << " (need at least 2 data points)" << endl;
        return;
    }

    // Calculate correlations using StatsCalculator
    SPCCResult result;
    m_stats.getsPCC(windSpeeds, temperatures, result.s_t);
    m_stats.getsPCC(windSpeeds, solarRadiation, result.s_r);
    m_stats.getsPCC(temperatures, solarRadiation, result.t_r);

    // Store in cache
    m_spccCache[month] = result;

    // Display results using ConsoleWriter
    m_writer.printOption3Result(month, result.s_t, result.s_r, result.t_r);
}
// Option 4: Using CSVReportWriter
void Menu::executeOption4(int year)
{
    if (!m_yearsWithData.SearchTree(year))
    {
        cout << endl;
        cout << "Year " << year << " not found." << endl;
        return;
    }

    Vector<MonthlyData> yearData;
    for (int i = 0; i < m_monthlyData.Size(); i++)
    {
        if (m_monthlyData[i].year == year)
        {
            yearData.Append(m_monthlyData[i]);
        }
    }

    for (int i = 0; i < yearData.Size() - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < yearData.Size(); j++)
        {
            if (yearData[j].month < yearData[minIndex].month)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            MonthlyData temp = yearData[i];
            yearData[i] = yearData[minIndex];
            yearData[minIndex] = temp;
        }
}
    // Use CSVReportWriter with monthlyData directly
    if (m_csvWriter.writeOption4("WindTempSolar.csv", year, yearData, m_rawRecords))
    {
        cout << endl;
        cout << "Summary Successfully Written to: WindTempSolar.csv" << endl;
    }
    else
    {
        cout << "Error: Could not write to file." << endl;
    }
}

void Menu::run()
{
    while (true)
    {
        displayOptions();

        int option;
        if (!readOption(option))
        {
            cout << "Invalid option. Please try again." << endl;
            continue;
        }

        if (option == 5)
        {
            cout << endl;
            cout << "===================================================================" << endl;
            cout << endl;
            cout << "Exiting the Program.... Thank you for Using." << endl;
            cout << endl;
            cout << "===================================================================" << endl;
            break;
        }

        if (option == 1)
        {
            int year, month;
            if (!readYear(year) || !readMonth(month))
            {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
            executeOption1(year, month);
        }
        else if (option == 2)
        {
            int year;
            if (!readYear(year))
            {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
            executeOption2(year);
        }
        else if (option == 3)
        {
            int month;
            if (!readMonth(month))
            {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
            executeOption3(month);
        }
        else if (option == 4)
        {
            int year;
            if (!readYear(year))
            {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
            executeOption4(year);
        }
    }
}
