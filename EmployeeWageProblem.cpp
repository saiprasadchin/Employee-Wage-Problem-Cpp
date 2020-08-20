#include <iostream>
#include <time.h>
#include <vector>
using namespace std;
int checkAttendance();
int wageCalculator(int);
int wagePerHour = 20;
const int totalWorkingDays = 20;
const int totalWorkingHours = 100;

int main()
{
    srand(time(NULL));
    int fullDayHour = 8;
    int partDayHour = 4;
    int noWorkDay = 0;
    int isPresent = 1;
    int isAbsent = 2;
    int isPartTime = 1;
    int isFullTime = 2;
    int totalWorkingDays = 20;
    int employeeWage;
    vector<int> employeeMonthlyWage;
    cout << "\n\n\n------------------------------------\n\n";
    cout << "\nWelcome to Employee Wage Problem\n"
         << endl;
    int workedDays = 0;
    int workedHours = 0;
    while (workedDays < totalWorkingDays && workedHours < totalWorkingHours)
    {
        int decideAttendance = ((rand() % 2) + 1);
        int decideTypeHours = ((rand() % 2) + 1);
        if (decideAttendance == isPresent)
        {
            cout << "Employee is present" << endl;
            if (decideTypeHours == isPartTime)
            {
                cout << "Part Time wage\n";
                employeeWage = wageCalculator(partDayHour);
                workedHours += partDayHour;
            }
            else
            {
                cout << "Full Time wage\n";
                employeeWage = wageCalculator(fullDayHour);
                workedHours += fullDayHour;
            }
            cout << "Employees wage for today : " << employeeWage << "\n"
                 << endl;
        }
        else
        {
            employeeWage = wageCalculator(noWorkDay);
            cout << "Employee is absent\n"
                 << endl;
        }
        employeeMonthlyWage.push_back(employeeWage);
        workedDays++;
    }
    int days = 0;
    for (int &wages : employeeMonthlyWage)
    {
        days++;
        std::cout << "Day " << days << " - Wage : " << wages << "\n";
    }
    return 0;
}

int wageCalculator(int hoursPassed)
{
    return wagePerHour * hoursPassed;
}