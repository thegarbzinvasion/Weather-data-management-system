#include "Menu.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Helper function that prints the menu statements and options to the console
void Menu::displayOptions() const
{
    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;
    cout << "--------------------- WEATHER RECORD SERVICES ---------------------" << endl;
    cout << endl;
    cout << "===================================================================" << endl;
    cout << endl;
    cout << "1. Average wind speed and sample standard deviation for this wind speed given a specified month and year" << endl;
    cout << "2. Average ambient air temperature and sample standard deviation for each month of a specified year" << endl;
    cout << "3. Total solar radiation in kWh/m2 for each month of a specified year" << endl;
    cout << "4. Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m2 for each month of a specified year" << endl;
    cout << "5. Exit" << endl;
}

// Helper function that helps read integer value provided by user and clears the buffer afterawards
bool Menu::readInt(const char* prompt, int& outValue) const
{
    cout << prompt;

    if(!(cin >> outValue))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }

    cin.ignore(10000, '\n'); // clear rest of line
    return true;
}

// Helper function that reads and validates option value
bool Menu::readOption(int& outOption) const
{
    int opt = 0;
    if(!readInt("Enter a VALID option (1-5): ", opt))
    {
        return false;
    }
    if(opt < 1 || opt > 5)
    {
        return false;
    }
    outOption = opt;
    return true;
}

// Helper function that reads and validates year value
bool Menu::readYear(int& outYear) const
{
    int y = 0;
    if(!readInt("Enter a VALID year (ex: 1905, 2016): ", y))
    {
        return false;
    }
    if(y <= 0)
    {
        return false;
    }

    outYear = y;
    return true;
}

// Helper function that reads and validates month value
bool Menu::readMonth(int& outMonth) const
{
    int m = 0;
    if(!readInt("Enter a VALID month (1-12): ", m))
    {
        return false;
    }
    if(m < 1 || m > 12)
    {
        return false;
    }

    outMonth = m;
    return true;
}

// Creates an instance of request struct and record values user entered (if they are valid) into request and returns it
Request Menu::getRequest() const
{
    Request request;
    request.option = 0;
    request.year = 0;
    request.month = 0;

    while(true)
    {
        displayOptions();

        int option = 0;
        if(!readOption(option))
        {
            cout << "===================================================================" << endl;
            cout << endl;
            cout << "Option entered is NOT listed between (1-5), Please Try again." << endl;
            cout << endl;
            cout << "===================================================================" << endl;
            continue;
        }

        request.option = option;

        if(option == 5)
        {
            return request; // Exit
        }

        int year = 0;

        if(!readYear(year))
        {
            cout << "===================================================================" << endl;
            cout << endl;
            cout << "Year entered is NOT valid. Please Try again." << endl;
            cout << endl;
            cout << "===================================================================" << endl;
        }

        request.year = year;

        if(option == 1)
        {
            int month = 0;
            if(!readMonth(month))
            {
            cout << "===================================================================" << endl;
            cout << endl;
            cout << "Month entered is NOT valid. Please Try again." << endl;
            cout << endl;
            cout << "===================================================================" << endl;
            }

            request.month = month;
        }

        else
        {
            request.month = 0; // Means month is not used (for option 2/3/4)
        }

        return request;
    }
}
