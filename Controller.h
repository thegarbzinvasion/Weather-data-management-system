#ifndef CONTROLLER_H
#define CONTROLLER_H

//---------------------------------------------------------------------------------

#include "Vector.h"
#include "Bst.h"
#include "MonthlyData.h"
#include "WeatherRecord.h"
#include <map>
#include <string>

//---------------------------------------------------------------------------------

/**
 * @struct SPCCResult
 * @brief Forward declaration of SPCCResult struct from Menu.h
 *
 * Stores the three correlation results for Option 3 (sPCC).
 * Defined in Menu.h
 */
struct SPCCResult;

/**
 * @class Controller
 * @brief Coordinates data loading, aggregation, and program execution.
 *
 * Handles reading CSV file names from a text file, loading weather data
 * from multiple CSV files, aggregating into monthly statistics, and
 * launching the menu for user interaction.
 *
 * @author Kyaw Okkar
 * @version 02
 * @date 03/04/2026
 */
class Controller
{
public:
    /**
     * @brief Main program execution - loads data and runs menu
     *
     * Orchestrates the entire program flow:
     * 1. Loads and aggregates data from CSV files
     * 2. Converts aggregated data to primary storage
     * 3. Creates and runs the menu for user options
     */
    void runProgram();

private:
    /**
     * @brief Loads all CSV files and aggregates into monthly data
     *
     * Phase 1: Reads CSV filenames from data_source.txt
     * Phase 2: Loads each CSV and aggregates directly into std::map
     * Phase 3: Converts map to Vector<MonthlyData> using WeatherDataProcessor
     *
     * @param outMonthlyData Output Vector of aggregated monthly statistics
     * @param outRawRecords Output Vector of raw WeatherRecord objects (for MAD)
     * @param outYears Output BST of all years that have data (for validation)
     * @param outMonths Output BST of all months that have data (for validation)
     * @return true if data loaded and aggregated successfully, false otherwise
     */
    bool loadAllData(Vector<MonthlyData>& outMonthlyData,
                     Vector<WeatherRecord>& outRawRecords,
                     Bst<int>& outYears,
                     Bst<int>& outMonths) const;

    /**
     * @brief Builds full CSV file path by prepending "data/" folder
     *
     * @param fileName Name of the CSV file (e.g., "weather_data.csv")
     * @return Full path string (e.g., "data/weather_data.csv")
     */
    std::string buildCsvPath(const std::string& fileName) const;
};

#endif // CONTROLLER_H
