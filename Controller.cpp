#include "Controller.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Coordinate classes DataSourceReader and CSVWeatherLoader to read and load data into outRecords
bool Controller::loadAllData(Vector<WeatherRecord>& outRecords) const
{
    DataSourceReader reader;
    CSVWeatherLoader loader;

    Vector<std::string> csvFileNames;

    const string dataSourcePath = "data/data_source.txt";

    if(!reader.readCsvFileName(dataSourcePath, csvFileNames))
    {
        cout << "Error: Could not read data source file: " << dataSourcePath << endl;
        return false;
    }

    for(int i = 0; i < csvFileNames.Size(); i++)
    {
        string csvPath = buildCsvPath(csvFileNames[i]);

        if(!loader.loadData(csvPath, outRecords))
        {
            cout << "Error: Could not load CSV file: " << csvPath << endl;
            return false;
        }

    cout << "===================================================================" << endl;
    cout << endl;
    cout << "Records Loaded from: " << csvPath << endl;
    }

    return true;
}

// Builds the required file path using "data/" to ensure the csv file is only from the "data" folder
string Controller::buildCsvPath(const string& fileName) const
{
    return std::string("data/") + fileName;
}

// Coordinate classes to calculate and display weather stats
void Controller::runProgram()
{
    Vector<WeatherRecord> weatherrecords;

    if(!loadAllData(weatherrecords))
    {
        return; // exit function immediately if loadAllDate() returns false
    }

    cout << "Number of Records Loaded: " << weatherrecords.Size() << endl;

    StatsCalculator stats;
    ConsoleWriter consoleWriter;
    CSVReportWriter csvWriter;

    Option1Service option1(stats, consoleWriter);
    Option2Service option2(stats, consoleWriter);
    Option3Service option3(stats, consoleWriter);
    Option4Service option4(stats, csvWriter);

    Menu menu;

    while(true)
    {
        Request request = menu.getRequest();

        if(request.option == 5)
        {
            cout << endl;
            cout << "===================================================================" << endl;
            cout << endl;
            cout << "Exiting the Program.... Thank you for Using." << endl;
            cout << endl;
            cout << "===================================================================" << endl;
            break;
        }

        if(request.option == 1)
        {
            option1.executeOption1(weatherrecords, request.year, request.month);
        }
        else if(request.option == 2)
        {
            option2.executeOption2(weatherrecords, request.year);
        }
        else if(request.option == 3)
        {
            option3.executeOption3(weatherrecords, request.year);
        }
        else if(request.option == 4)
        {
            option4.executeOption4(weatherrecords, request.year, "WindTempSolar.csv");
            cout << endl;
            cout << endl;
            cout << "Summary Successfully Written to: WindTempSolar.csv" << endl;
            cout << endl;
        }
        else
        {
            cout << "Invalid option." << endl;
        }
    }
}
