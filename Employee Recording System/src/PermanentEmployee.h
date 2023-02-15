#ifndef AS2_2_PERMANENTEMPLOYEE_H
#define AS2_2_PERMANENTEMPLOYEE_H
#include "Employee.h"

class PermanentEmployee: public Employee {

public:
    PermanentEmployee(int employeeNumber1, int employeeType1, string name1, string surname1, string title1, double salaryCoefficient1,
                      const string &birthDate1, const string &dateOfAppointment, int lengthService1);
};


#endif //AS2_2_PERMANENTEMPLOYEE_H
