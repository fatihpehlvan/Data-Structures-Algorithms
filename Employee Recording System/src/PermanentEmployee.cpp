#include "PermanentEmployee.h"

PermanentEmployee::PermanentEmployee(int employeeNumber1, int employeeType1, string name1, string surname1, string title1,
                                     double salaryCoefficient1,
                                     const string &birthDate1, const string &dateOfAppointment, int lengthService1)
        : Employee(employeeNumber1, employeeType1, name1, surname1, title1, salaryCoefficient1, birthDate1, dateOfAppointment, lengthService1) {

}
