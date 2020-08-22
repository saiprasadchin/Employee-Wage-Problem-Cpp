
#include <iostream>
#include <time.h>
#include <ctime>
#include <list>
#include <vector>
#include <fstream>
#include <bits/stdc++.h> 
#include <algorithm>
#include <unistd.h>
using namespace std; 
int static totalEmpHrs = 0;
struct Company
{
    string companyName;
    int wagePerHour;
    int workingDays;
    int maxHours;
};

struct EmployeeDaily
{
    string empName;
    int dayNo;
    int wagePerHour;
    int hours;
    int wage;
    int monthNo;
    string companyName;
};

struct EmployeeMonthly
{
    string empName;
    int wagePerHour;
    int totalHours;
    int monthlyWage;
    int monthNo;
    string companyName;
};

Company Jio;
Company Reliance;
void registerCompany()
{
    Jio.companyName = "Jio";
    Jio.maxHours = 130;
    Jio.wagePerHour = 50;
    Jio.workingDays = 5;

    Reliance.companyName = "Reliance";
    Reliance.maxHours = 100;
    Reliance.wagePerHour = 30;
    Reliance.workingDays = 7;
}
vector<EmployeeMonthly*> monthlyEmpList;
vector<EmployeeDaily*> dailyEmpList;

Company company;


void writeEmployeeDataDailyCSV()
{
    fstream employeeFile;
    employeeFile.open("EmpDailyData.csv", ios::out | ios::trunc);
    if (employeeFile.is_open())
    {
        for (auto i = dailyEmpList.begin(); i != dailyEmpList.end(); ++i){
        employeeFile <<(*i)->empName;
        employeeFile << ", "<<(*i)->dayNo;
        employeeFile << ", "<<(*i)->wagePerHour;
        employeeFile << ", "<<(*i)->hours;
        employeeFile << ", "<<(*i)->wage;
        employeeFile << ", "<<(*i)->monthNo;
        employeeFile << ", "<<(*i)->companyName<<endl;
    }
        cout << endl;
    }
    employeeFile.close();
}
void writeEmployeeDataCSV()
{
    fstream employeeFile;
    employeeFile.open("EmpMonthlyData.csv", ios::out | ios::trunc);
    if (employeeFile.is_open())
    {
        employeeFile << "EmpName"
                     << ", "
                     << "totalHours"
                     << ", "
                     << "monthlyWage"
                     << ", "
                     << "wagePerHour"
                     << ", "
                     << "companyName"
                     << ", "<<endl;
        for (auto i = monthlyEmpList.begin(); i != monthlyEmpList.end(); ++i){
        employeeFile <<(*i)->empName;
        employeeFile << ", "<<(*i)->totalHours;
        employeeFile << ", "<<(*i)->monthlyWage;
        employeeFile << ", "<<(*i)->wagePerHour;
        employeeFile << ", "<<(*i)->companyName<<endl;
    }
        cout << endl;
    }
    employeeFile.close();
}
int getMonthlyEmployeeHours()
{
    return totalEmpHrs;
}

int getDailyEmployeeHours()
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    int empHrs = 0;
    int empCheck = rand() % 3;
    switch (empCheck)
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
    return empHrs;
}

void employeeMonthly( Company company, string empName)
{
    EmployeeMonthly *emp;
    emp = new EmployeeMonthly;
    emp->empName = empName;
    emp->totalHours = getMonthlyEmployeeHours();
    emp->monthlyWage = emp->totalHours * company.wagePerHour;
    emp->wagePerHour = company.wagePerHour;
    emp->companyName = company.companyName;

    monthlyEmpList.push_back(emp);
    writeEmployeeDataCSV();
}
void employeeDaily( Company company)
{
    string empName;
    cout << "Enter Employee name " << endl;
    cin >> empName;

    int NUM_OF_WORKING_DAYS = company.workingDays;
    int MAX_HRS_IN_MONTH = company.maxHours;
    totalEmpHrs = 0;
    int totalWorkingDays = 0;

    while ( totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays < NUM_OF_WORKING_DAYS)
    {
        totalWorkingDays++;
        EmployeeDaily *empDaily;
        empDaily = new EmployeeDaily;
        empDaily->empName = empName;
        empDaily->dayNo = totalWorkingDays;
        empDaily->hours = getDailyEmployeeHours();
        empDaily->wage = empDaily->hours * company.wagePerHour;
        empDaily->wagePerHour = company.wagePerHour;
        empDaily->monthNo = 1;
        empDaily->companyName = company.companyName;

        dailyEmpList.push_back(empDaily);
        totalEmpHrs += empDaily->hours;
    }
    employeeMonthly(company, empName);    
    writeEmployeeDataDailyCSV();
}

void display()
{
    for (auto i = monthlyEmpList.begin(); i != monthlyEmpList.end(); ++i){
        cout<<"Name        : "<<(*i)->empName <<endl;
        cout<<"totalHours  : "<<(*i)->totalHours <<endl;
        cout<<"monthlyWage : "<<(*i)->monthlyWage <<endl;
        cout<<"wagePerHour : "<<(*i)->wagePerHour <<endl;
        cout<<"companyName : "<<(*i)->companyName <<endl;
        cout<<"==================================="<<endl;
    }
}

void selectCompany()
{
    int selectCompanyName = 0;
    cout<<"\nSeclec Company : ";
    cout << "\n1) Jio \n2) Reliance : ";
    cin >> selectCompanyName;
    switch (selectCompanyName)
    {
        case 1: 
            employeeDaily( Jio );
            break;
        case 2:
            employeeDaily( Reliance );
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
    }
}
bool compareDailyWages(EmployeeDaily* i1, EmployeeDaily* i2) 
{ 
    return ( i1->wage < i2->wage ); 
}
void sortByDailyWages()
{
    sort(dailyEmpList.begin(), dailyEmpList.end(), compareDailyWages);
    cout<<"==================================="<<endl;
    for (auto i = dailyEmpList.begin(); i != dailyEmpList.end(); ++i){
        cout<<"Name        : "<<(*i)->empName <<endl;
        cout<<"CompanyName : "<<(*i)->companyName <<endl;
        cout<<"DayNo       : "<<(*i)->dayNo <<endl;
        cout<<"WagePerHour : "<<(*i)->wagePerHour <<endl;
        cout<<"Hours       : "<<(*i)->hours <<endl;
        cout<<"Wage        : "<<(*i)->wage <<endl;
        cout<<"MonthNo     : "<<(*i)->monthNo <<endl;
        cout<<"==================================="<<endl;
    }
}
bool compare(EmployeeMonthly* i1, EmployeeMonthly* i2) 
{ 
    return ( i1->monthlyWage < i2->monthlyWage ); 
}
void sortByMonthlyWages( vector<EmployeeMonthly*> companyList)
{
    sort(companyList.begin(), companyList.end(), compare);
    cout<<"==================================="<<endl;
    for (auto i = companyList.begin(); i != companyList.end(); ++i){
        cout<<"Name        : "<<(*i)->empName <<endl;
        cout<<"totalHours  : "<<(*i)->totalHours <<endl;
        cout<<"monthlyWage : "<<(*i)->monthlyWage <<endl;
        cout<<"wagePerHour : "<<(*i)->wagePerHour <<endl;
        cout<<"companyName : "<<(*i)->companyName <<endl;
        cout<<"==================================="<<endl;
    }
}
void filterByCompany( Company company )
{
    vector<EmployeeMonthly*> listByCompany;
    for (auto i = monthlyEmpList.begin(); i != monthlyEmpList.end(); ++i){
        if( (*i)->companyName == company.companyName )
            listByCompany.push_back(*i);
    }
    sortByMonthlyWages( listByCompany );
}
void displayMonthlyWagesByCompany()
{
    int selectCompanyName = 0;
    cout<<"\nSeclec Company : ";
    cout << "\n1) Jio \n2) Reliance : ";
    cin >> selectCompanyName;
    switch (selectCompanyName)
    {
        case 1: 
            filterByCompany( Jio );
            break;
        case 2:
            filterByCompany( Reliance );
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
    }

}
int main()
{
    sleep(1.8);
    srand(time(0));
    registerCompany();
    bool endKey = true;
    while (endKey)
    {
        int choice = 0;
        cout << "\n1) InsertEmployee \n2) Display \n3) Monthly Wages By Company \n4) Sort By daily Wages \n5) Sort By Monthly Wages \n6) Employee Details By Wages \n7) Exit : ";
        cin >> choice;
        switch (choice)
        {
            case 1: 
                selectCompany();
                break;
            case 2:
                display();
                break;
            case 3:
                displayMonthlyWagesByCompany();
                break;
            case 4:
                sortByDailyWages();
                break;
            case 5:
                //sortByMonthlyWages( monthlyEmpList );
                break;
            case 6:
                //getEmployeeDetailsByWages();
                break;
            case 7:
                endKey = false;
                break;
            default:
                cout << "Invalid Input" << endl;
                break;
        }
    }
    return 0;
}