#ifndef MONTHLYDATA_H
#define MONTHLYDATA_H

/**
 * @struct MonthlyData
 * @brief Final storage structure for aggregated monthly weather statistics.
 *
 * Contains calculated averages, standard deviations, and total solar radiation
 * for a specific month and year. Used as primary storage for all calculations.
 *
 * @author Kyaw Okkar
 * @version 01
 * @date 03/04/2026
 */

struct MonthlyData
{
    int year;                    ///< Year (e.g., 2015)
    int month;                   ///< Month number (1-12)
    double avgWindSpeed;         ///< Average wind speed (m/s)
    double windStdDev;           ///< Sample standard deviation of wind speed (m/s)
    double avgTemperature;       ///< Average temperature (°C)
    double tempStdDev;           ///< Sample standard deviation of temperature (°C)
    double totalSolarRadiation;  ///< Total solar radiation (W/m²)

    /**
     * @brief Default constructor - initializes all values to 0
     */
    MonthlyData()
        : year(0), month(0), avgWindSpeed(0), windStdDev(0),
          avgTemperature(0), tempStdDev(0), totalSolarRadiation(0) {}
};

#endif // MONTHLYDATA_H
