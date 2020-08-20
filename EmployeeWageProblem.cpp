#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>

using namespace std;
void writeEmployeeDataCSV(int);
vector<int*> totalMonthlyWages;

void writeEmployeeDataCSV(int totalMonths) {
    ofstream employeeFile;
    employeeFile.open("EmployeeData.csv", ios::out | ios::trunc);
    if (employeeFile.is_open())
    {
        employeeFile << "Employee";
        for (int month = 0; month < totalMonths ;month++)
        {
            employeeFile << ", Month_" << month + 1;
        }
        int* arr;
        for (int employee = 0; employee < totalMonthlyWages.size(); employee++)
        {
            employeeFile << "\nEmployee_" << (employee + 1);
            arr = totalMonthlyWages[employee];
            for (int month = 0; month < totalMonths; month++)
            {
                employeeFile << ", " << *arr++;
            }
             
        }
    }
    employeeFile.close();
}

int getEmployeeHours() {
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    const int NUM_OF_WORKING_DAYS = 20;
    const int MAX_HRS_IN_MONTH = 100;
   
    int empHrs = 0;
    int totalEmpHrs = 0;
    int totalWorkingDays = 0;
    
    while(totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays <= NUM_OF_WORKING_DAYS)
    {
        totalWorkingDays++;
        int empCheck = rand() % 3;
        switch(empCheck)
        {
            case IS_PART_TIME:
                empHrs = 4;
                break;
            case IS_FULL_TIME:
                empHrs = 8;
                break;
            default:
                empHrs = 0;
                break;
        }
        totalEmpHrs += empHrs;
    }
    return totalEmpHrs;
}


int main()
{
    srand(time(NULL));
    const int EMP_RATE_PER_HOUR = 20;
    int totalEmployees;
    cout << "\nEnter total number of employees. \n";
    cin >> totalEmployees;
    
    int totalMonths;
    cout << "\nEnter nunber of Months. \n";
    cin >> totalMonths;
    
    for (int i = 0; i < totalEmployees; i++)
    {
        int* monthlyWages = new int[totalMonths];
        for (int i = 0; i < totalMonths; i++)
        {
            int empWage = getEmployeeHours() * EMP_RATE_PER_HOUR;
            monthlyWages[i] = empWage;
            cout << "Monthly Wage for Employee_" << (i + 1) << " : "<<empWage<<endl;   
        }
        totalMonthlyWages.push_back(monthlyWages); 
        
    }
    writeEmployeeDataCSV(totalMonths);
    return 0;
}