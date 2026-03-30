#include "DataSourceReader.h"
#include <fstream>
#include "Vector.h"s

// reads the csv file name provided in the txt file and passes it to each index in Vector<string> csvFileNames
bool DataSourceReader::readCsvFileName(const std::string& txtPath, Vector<std::string>& csvFileNames) const
{
    std::ifstream infile(txtPath);
    if(!infile)
    {
        return false;
    }

    std::string line;
    int index = 0;

    while(std::getline(infile, line)) // reads first line of txt file
    {
        bool hasNonWhiteSpace = false;

        for(int i = 0; i < line.size(); i++) // reads each character of the line
        {
            if(line[i] != ' ' && line[i] != '\t' && line[i] != '\r') // if a space, tab, or \r r not present for all characters
            {
                hasNonWhiteSpace = true; // set hasNonWhiteSpace to true
                break;
            }
        }
        if(hasNonWhiteSpace) // if the line have no whitespace
        {
            if(line.back() == '\r') // whether the the end of the line hv the character '\r' or not
            {
                line.pop_back(); // if so remove (optional)
            }
            csvFileNames.Insert(index, line);
            index++;
        }
    }
    return true;
}
