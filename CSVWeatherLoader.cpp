#include "CSVWeatherLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>

// Used to store the mapped header fields
enum FieldType
{
    FIELD_IGNORE,
    FIELD_WAST,
    FIELD_WIND,
    FIELD_SOLAR,
    FIELD_TEMP
};

bool CSVWeatherLoader::loadData(const std::string& csvPath,
                                std::map<std::string, MonthlyAggregate>& outMap,
                                Bst<int>& yearsWithData,
                                Bst<int>& monthsWithData,
                                Vector<WeatherRecord>& outRawRecords) const
{
    std::ifstream infile(csvPath);
    if (!infile)
    {
        std::cout << "Error: Could not open file: " << csvPath << std::endl;
        return false;
    }

    Vector<FieldType> colMap;
    std::string headersLine;
    std::string field;
    std::string line;

    // Read header line
    if (!std::getline(infile, headersLine))
    {
        std::cout << "FAILED: could not read header line." << std::endl;
        return false;
    }

    // Parse header to create column mapping
    std::stringstream headerSS(headersLine);
    while (std::getline(headerSS, field, ','))
    {
        std::string normalized = "";
        for (int i = 0; i < field.size(); i++)
        {
            if (field[i] != ' ')
            {
                char upperChar = std::toupper(field[i]);
                normalized += upperChar;
            }
        }

        FieldType mappedField = FIELD_IGNORE;

        // Match header names to field types
        if (normalized == "WAST")
        {
            mappedField = FIELD_WAST;
        }
        else if (normalized == "S")
        {
            mappedField = FIELD_WIND;
        }
        else if (normalized == "T")
        {
            mappedField = FIELD_TEMP;
        }
        else if (normalized == "SR")
        {
            mappedField = FIELD_SOLAR;
        }

        colMap.Append(mappedField);
    }

    // Track unique timestamps to detect duplicates within this file
    Bst<std::string> uniqueTimestamps;

    // Process each data row
    while (std::getline(infile, line))
    {
        // Temporary variables for this row
        int day = 0, month = 0, year = 0;
        int hour = 0, minute = 0;
        float windSpeed = 0.0f;
        float solarRadiation = 0.0f;
        float ambientAirTemp = 0.0f;

        bool hasDate = false;
        bool hasWind = false;
        bool hasSolar = false;
        bool hasTemp = false;

        std::stringstream rowSS(line);
        int columnIndex = 0;

        // Parse each column based on its mapped type
        while (std::getline(rowSS, field, ','))
        {
            if (columnIndex >= colMap.Size())
            {
                break;
            }

            FieldType type = colMap[columnIndex];

            if (type == FIELD_WAST)
            {
                // Parse date and time from WAST column
                if (!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }

                std::stringstream wastSS(field);
                std::string dataPart;
                std::string timePart;

                wastSS >> dataPart >> timePart;

                std::stringstream dateSS(dataPart);
                char slash;
                dateSS >> day >> slash >> month >> slash >> year;

                std::stringstream timeSS(timePart);
                char colon;
                timeSS >> hour >> colon >> minute;

                hasDate = true;
            }
            else if (type == FIELD_WIND)
            {
                // Parse wind speed
                if (!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }
                if (field != "" && field != "N/A")
                {
                    windSpeed = std::stof(field);
                    hasWind = true;
                }
            }
            else if (type == FIELD_SOLAR)
            {
                // Parse solar radiation
                if (!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }
                if (field != "" && field != "N/A")
                {
                    solarRadiation = std::stof(field);
                    hasSolar = true;
                }
            }
            else if (type == FIELD_TEMP)
            {
                // Parse temperature
                if (!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }
                if (field != "" && field != "N/A")
                {
                    ambientAirTemp = std::stof(field);
                    hasTemp = true;
                }
            }
            columnIndex++;
        }

        // Only aggregate if we have at least a date
        if (hasDate)
        {
            // Create unique timestamp key for duplicate detection
            std::string timestampKey = std::to_string(day) + "/" +
                                       std::to_string(month) + "/" +
                                       std::to_string(year) + " " +
                                       std::to_string(hour) + ":" +
                                       std::to_string(minute);

            // Check for duplicate record within this file
            if (uniqueTimestamps.SearchTree(timestampKey))
            {
                std::cout << "Warning: Duplicate timestamp found in " << csvPath
                          << ": " << timestampKey << " - skipping" << std::endl;
                continue;
            }

            // Add to BST of seen timestamps
            uniqueTimestamps.InsertTree(timestampKey);

            // Create a WeatherRecord for raw storage (MAD calculations)
            Date date(day, month, year);
            Time time(hour, minute);

            WeatherRecord record;
            record.setDate(date);
            record.setTime(time);

            if (hasWind)
            {
                record.setWindSpeed(windSpeed);
            }
            if (hasTemp)
            {
                record.setAmbientAirTemp(ambientAirTemp);
            }
            if (hasSolar)
            {
                record.setSolarRadiation(solarRadiation);
            }

            // Store raw record for MAD calculations
            outRawRecords.Append(record);

            // Create key "Month-Year"
            std::string monthYearKey = std::to_string(month) + "-" + std::to_string(year);

            // Get or create the aggregate for this month-year
            MonthlyAggregate& agg = outMap[monthYearKey];

            // Add the reading to the aggregate
            if (hasWind)
            {
                agg.addWindSpeed(windSpeed);
            }
            if (hasTemp)
            {
                agg.addTemperature(ambientAirTemp);
            }
            if (hasSolar)
            {
                agg.addSolarRadiation(solarRadiation);
            }
            agg.incrementCount();

            // Track years and months in BST (set operations)
            yearsWithData.InsertTree(year);
            monthsWithData.InsertTree(month);
        }
    }

    return true;
}
