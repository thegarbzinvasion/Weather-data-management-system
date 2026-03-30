#include "CSVWeatherLoader.h"
#include "Vector.h"
#include "WeatherRecord.h"
#include "Date.h"
#include "Time.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype> // To check uppercase or lowercase

// Used to store the mapped header fields (1st row) in the csv file which represents one of the values stored in here
enum FieldType
{
    FIELD_IGNORE,
    FIELD_WAST,
    FIELD_WIND,
    FIELD_SOLAR,
    FIELD_TEMP
};

// Loads weather data from the specified csvPath and does mapping of header rows to column data
bool CSVWeatherLoader::loadData(const std::string & csvPath, Vector<WeatherRecord> & outweatherrecords) const
{
    std::ifstream infile(csvPath);
    if(!infile)
    {
        return false;
    }

    Vector<FieldType> colMap;

    std::string headersLine;
    std::string field;
    std::string line;

    if(!std::getline(infile, headersLine))
    {
        std::cout << "FAILED: could not read header line." << std::endl;
        return false;
    }

    std::stringstream headerSS(headersLine);

    while (std::getline(headerSS, field, ','))
    {
        std::string normalized = "";

        for(int i = 0; i < field.size(); i++)
        {
            if(field[i] != ' ')
            {
                char upperChar = std::toupper(field[i]);
                normalized += upperChar;
            }
        }

        FieldType mappedField;

        if(normalized == "WAST")
        {
            mappedField = FIELD_WAST;

        }else if(normalized == "S")
        {
            mappedField = FIELD_WIND;

        }else if(normalized == "T")
        {
            mappedField = FIELD_TEMP;

        }else if(normalized == "SR")
        {
            mappedField = FIELD_SOLAR;
        }
        else
        {
            mappedField = FIELD_IGNORE;
        }

        colMap.Append(mappedField);
    }

    while(std::getline(infile, line))
    {

        WeatherRecord weatherrecord;

        std::stringstream rowSS(line);
        int columnIndex = 0;

        while(std::getline(rowSS, field, ','))
        {
            if(columnIndex >= colMap.Size())
            {
                break;
            }

            FieldType type = colMap[columnIndex];

            if(type == FIELD_WAST)
            {
                if(!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }

                std::stringstream wastSS(field);

                std::string dataPart;
                std::string timePart;

                wastSS >> dataPart >> timePart;

                std::stringstream dateSS(dataPart);

                int day, month, year;
                char slash;

                dateSS >> day >> slash >> month >> slash >> year;

                std::stringstream timeSS(timePart);

                int hour, minute;
                char colon;

                timeSS >> hour >> colon >> minute;

                Date d(day, month, year);
                Time t(hour, minute);

                weatherrecord.setDate(d);
                weatherrecord.setTime(t);

            }else if(type == FIELD_WIND)
            {
                if(!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }
                if(field != "" && field != "N/A")
                {
                    float value = std::stof(field);
                    weatherrecord.setWindSpeed(value);
                }

            }else if(type == FIELD_SOLAR)
            {

                if(!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }
                if(field != "" && field != "N/A")
                {
                    float value = std::stof(field);
                    weatherrecord.setSolarRadiation(value);
                }

            }else if(type == FIELD_TEMP)
            {

                if(!field.empty() && field.back() == '\r')
                {
                    field.pop_back();
                }
                if(field != "" && field != "N/A")
                {
                    float value = std::stof(field);
                    weatherrecord.setAmbientAirTemp(value);
                }
            }
            columnIndex++;
        }
        outweatherrecords.Append(weatherrecord);
    }

    return true;
}
