#ifndef DATASOURCEREADER_H
#define DATASOURCEREADER_H

//---------------------------------------------------------------------------------

#include <string>
#include "Vector.h"

//---------------------------------------------------------------------------------

/**
 * @class DataSourceReader
 * @brief Reads the CSV file name from a text configuration file.
 *
 * Used to determine which CSV file should be loaded
 * by the program.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 15/02/2026
 */

class DataSourceReader
{
public:
    /**
     * @brief Reads CSV file name from text file
     * @return bool True if file name successfully read
     */
    bool readCsvFileName(const std::string& txtPath, Vector<std::string>& csvFileNames) const;
};

#endif // DATASOURCEREADER_H
