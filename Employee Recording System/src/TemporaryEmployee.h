#ifndef AS2_2_TEMPORARYEMPLOYEE_H
#define AS2_2_TEMPORARYEMPLOYEE_H
#include "Employee.h"

class TemporaryEmployee: public Employee {
public:
    TemporaryEmployee(int employeeNumber, int employeeType, string name, string surname, string title, double salaryCoefficient,
                      const string &birthDate, const string &dateOfAppointment, int lengthService);
}
;

#endif //AS2_2_TEMPORARYEMPLOYEE_H
