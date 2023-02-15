#include "Employee.h"

#include <iostream>

Employee::Employee(int employeeNumber, int employeeType, string name, string surname, string title, double salaryCoefficient,
                   const string &birthDate, const string &date2, int lengthService) {
    this->employeeNumber = employeeNumber;
    this->name = name;
    this->employeeType = employeeType;
    this->surname = surname;
    this->title = title;
    this->salaryCoefficient = salaryCoefficient;
    dateOfBirth = new Date (birthDate);
    dateOfAppointment = new Date (date2);
    this->lengthService = lengthService;
}

int Employee::getEmployeeNumber() const {
    return employeeNumber;
}

int Employee::getEmployeeType() const {
    return employeeType;
}


double Employee::getSalaryCoefficient() const {
    return salaryCoefficient;
}

void Employee::setSalaryCoefficient(double salaryCoefficient) {
    Employee::salaryCoefficient = salaryCoefficient;
}

int Employee::getLengthService() const {
    return lengthService;
}

const std::string &Employee::getName() const {
    return name;
}

const std::string &Employee::getSurname() const {
    return surname;
}

const std::string &Employee::getTitle() const {
    return title;
}

void Employee::setTitle(const std::string &title) {
    Employee::title = title;
}

const Date* Employee::getDateOfAppointment() const {
    return dateOfAppointment;
}

const Date* Employee::getDateOfBirth() const {
    return dateOfBirth;
}
//getInfo prints employee info in the console.
void Employee::getInfo() {
    string emptype;
    if (getEmployeeType() == 0) emptype = "Temporary";
    else emptype = "Permanent";
    cout << "Employee Number:\n" << getEmployeeNumber() << "\nEmployeeType:\n"<< emptype << "\nEmployee Name:\n" << getName() <<"\nEmployeeSurname:\n" << getSurname() << endl;
    cout << "Employee Title:\n" <<getTitle() << "\nEmployee Salary Coefficient:\n" << getSalaryCoefficient() << "\nEmployee Birth Date:\n" << getDateOfBirth()->getDay() << "-";
    cout << getDateOfBirth()->getMonth() << "-" << getDateOfBirth()->getYear() << "\nEmployee Appointment Date:\n";
    cout << getDateOfAppointment()->getDay() << "-" << getDateOfAppointment()->getMonth() << "-";
    cout << getDateOfAppointment()->getYear() << "\nEmployee Length Service:\n" << getLengthService() << "\n\n" << endl;
}



