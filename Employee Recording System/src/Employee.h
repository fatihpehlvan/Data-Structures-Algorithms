#ifndef AS2_2_EMPLOYEE_H
#define AS2_2_EMPLOYEE_H

#include <iostream>
#include "Date.h"
using namespace std;


class Employee {
private:
    int employeeNumber;
    int employeeType;
    string name;
    string surname;
    string title;
    double salaryCoefficient;
    Date* dateOfBirth;
    Date* dateOfAppointment;
    int lengthService;
public:

    Employee(int employeeNumber, int employeeType, string name, string surname, string title, double salaryCoefficient,const string& birthDate, const string& dateOfAppointment, int lengthService = 0);

    int getEmployeeNumber() const;

    const Date* getDateOfBirth() const;

    const Date* getDateOfAppointment() const;

    void getInfo();

    int getEmployeeType() const;

    double getSalaryCoefficient() const;

    void setSalaryCoefficient(double salaryCoefficient);

    int getLengthService() const;

    const std::string &getName() const;

    const std::string &getSurname() const;

    const std::string &getTitle() const;

    void setTitle(const std::string &title);
};

#endif //AS2_2_EMPLOYEE_H