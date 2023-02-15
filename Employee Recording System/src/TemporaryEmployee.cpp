#include "TemporaryEmployee.h"

TemporaryEmployee::TemporaryEmployee(int employeeNumber, int employeeType1, string name, string surname, string title,
                                     double salaryCoefficient, const string &birthDate,
                                     const string &dateOfAppointment, int lengthService) : Employee(employeeNumber, employeeType1, name, surname, title, salaryCoefficient, birthDate, dateOfAppointment, lengthService) {

}
