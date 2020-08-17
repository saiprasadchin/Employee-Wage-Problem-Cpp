#include <iostream>
#include <time.h>
using namespace std;
int checkAttendance();
int wageCalculator();
const int wagePerHour = 20;
const int fullDayHour = 8;
int main() {
    int isPresent = 1;
    int isAbsent = 2;
    int employeeWage;
    cout << "\n\n\n------------------------------------\n\n";
    cout << "\nWelcome to Employee Wage Problem\n" << endl;
    int attendance = checkAttendance();
    if (attendance == isPresent) {
        cout << "Employee is present" << endl;
        employeeWage = wageCalculator();
        cout << "Employees wage for today : " << employeeWage << endl;
    }
    else
        cout << "Employee is absent" << endl;


    return 0;
}
int checkAttendance(){
    srand(time(NULL));
	return ((rand() % 2) + 1);
}

int wageCalculator(){
    return wagePerHour * fullDayHour;
}
