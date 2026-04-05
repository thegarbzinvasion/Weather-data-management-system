#include "Controller.h"
#include "CSVWeatherLoader.h"
#include "WeatherDataProcessor.h"
#include "DataSourceReader.h"
#include "Menu.h"
#include "MonthlyAggregate.h"
#include "MonthlyData.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Builds the required file path using "data/" to ensure the csv file is only from the "data" folder
string Controller::buildCsvPath(const string& fileName) const
{
    return string("data/") + fileName;
}

// Phase 1 & 2: Load CSV files, aggregate into Map, then convert to Vector
bool Controller::loadAllData(Vector<MonthlyData>& outMonthlyData,
                              Vector<WeatherRecord>& outRawRecords,
                              Bst<int>& outYears,
                              Bst<int>& outMonths) const
{
    DataSourceReader reader;
    CSVWeatherLoader loader;
    Vector<string> csvFileNames;

    const string dataSourcePath = "data/data_source.txt";

    // Read the list of CSV filenames from the text file
    if (!reader.readCsvFileName(dataSourcePath, csvFileNames))
    {
        cout << "Error: Could not read data source file: " << dataSourcePath << endl;
        return false;
    }

    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;
    cout << "                     LOADING WEATHER DATA                          " << endl;
    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;

    // Phase 1: Aggregate into Map using Month-Year keys
    std::map<string, MonthlyAggregate> tempMap;
    Bst<int> yearsWithData;
    Bst<int> monthsWithData;

    outRawRecords.Clear();

    // Loop through each CSV file and load data
    for (int i = 0; i < csvFileNames.Size(); i++)
    {
        string csvPath = buildCsvPath(csvFileNames[i]);

        // Load and aggregate directly into Map
        if (!loader.loadData(csvPath, tempMap, yearsWithData, monthsWithData, outRawRecords))
        {
            cout << "Error: Could not load CSV file: " << csvPath << endl;
            return false;
        }

        cout << "   -> Loaded: " << csvPath << endl;
    }

    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "   Total raw records loaded: " << outRawRecords.Size() << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;

    // Phase 2: Convert Map to Vector (primary storage)
    WeatherDataProcessor processor;
    ProcessedData processed = processor.convertToVector(tempMap);

    // Copy results to output parameters
    outMonthlyData = processed.monthlyData;
    outYears = processed.yearsWithData;
    outMonths = processed.monthsWithData;

    return true;
}

// Coordinate classes to calculate and display weather stats
void Controller::runProgram()
{
    Vector<MonthlyData> monthlyData;
    Vector<WeatherRecord> rawRecords;
    Bst<int> yearsWithData;
    Bst<int> monthsWithData;
    std::map<int, SPCCResult> spccCache;

    // Load and aggregate all data
    if (!loadAllData(monthlyData, rawRecords, yearsWithData, monthsWithData))
    {
        cout << "Failed to load data. Exiting program." << endl;
        return;
    }

    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "   Total monthly records loaded: " << monthlyData.Size() << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;

    // Create and run the menu with loaded data
    Menu menu(monthlyData, rawRecords, yearsWithData, monthsWithData, spccCache);
    menu.run();
}
