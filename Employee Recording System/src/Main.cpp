#include <iostream>
#include "CircularArrayLinkedList.h"
#include "DoubleDynamicLinkedList.h"
using namespace std;

int main() {
    auto* crArray = new CircularArrayLinkedList;
    auto* sortedCrArray = new CircularArrayLinkedList;
    auto* dyArray = new DoubleDynamicLinkedList;
    auto* sortedDyArray = new DoubleDynamicLinkedList;

    while (true){
        int choose, employeeNumber, serviceDay, employeeType;
        string name, surname, title, birthDate, appointmentDate;
        double salaryCoefficient;
        cout << "___Employee Recording System___\nPlease select for the following Menu Operation:" << endl;
        cout << "1) Appointment of a new employee\n2) Appointment of a transferred employee\n3) Updating the title and salary coefficient of an employee" << endl;
        cout << "4) Deletion of an employee\n5) Listing the information of an employee\n6) Listing employees ordered by employee number" << endl;
        cout << "7) Listing employees ordered by appointment date\n8) Listing employees appointed after a certain date\n9) Listing employees assigned in a given year" << endl;
        cout << "10) Listing employees born before a certain date\n11) Listing employees born in a particular month\n12) Listing the information of the last assigned employee with a given title" << endl;
        cin >> choose;

        if(choose == 1 || choose == 2){
            cout << "Please type the employee number" << endl;
            cin >> employeeNumber;
            if (crArray->search(employeeNumber) != nullptr || dyArray->search(employeeNumber) != nullptr) continue;
            cout << "Type the employee type" << endl;
            cin >> employeeType;
            cout << "Type the name" << endl;
            cin.ignore();
            getline(std::cin, name);
            cout << "Type the surname" << endl;
            cin >> surname;
            cout << "Type the title" << endl;
            cin.ignore();
            getline(cin, title);
            cout << "Type salary coefficient" << endl;
            cin >> salaryCoefficient;
            cout << "Type birth date" << endl;
            cin >> birthDate;
            cout << "Type appointment date" << endl;
            cin >> appointmentDate;
            if (choose == 2){
                cout << "Type length of service days" << endl;
                cin >> serviceDay;
            } else serviceDay = 0;
            if (employeeType == 0){
                auto* newTemp = new TemporaryEmployee(employeeNumber, 0, name,surname, title,
                                                      salaryCoefficient, birthDate,appointmentDate,serviceDay);
                crArray->insertAfter(newTemp);
                sortedCrArray->insertAfter(newTemp);
            } else{
                auto* newPerm = new PermanentEmployee(employeeNumber, 1, name,surname, title,
                                                      salaryCoefficient, birthDate,appointmentDate,serviceDay);
                dyArray->insertAfter(newPerm);
                sortedDyArray->insertAfter(newPerm);
            }
        } else if (choose == 3){
            cout << "Please type the employee number" << endl;
            cin >> employeeNumber;
            TemporaryEmployee* findTemp = crArray->search(employeeNumber);
            PermanentEmployee* findPerm = dyArray->search(employeeNumber);
            if (findTemp != nullptr) {
                cout << "Update Title" << endl;
                cin >> title;
                findTemp->setTitle(title);
                cout << "Update Salary Coefficient" << endl;
                cin >> salaryCoefficient;
                findTemp->setSalaryCoefficient(salaryCoefficient);
            } else if(findPerm != nullptr){
                cout << "Update Title" << endl;
                cin >> title;
                findPerm->setTitle(title);
                cout << "Update Salary Coefficient" << endl;
                cin >> salaryCoefficient;
                findPerm->setSalaryCoefficient(salaryCoefficient);
            }
        } else if (choose == 4){
            cout << "Please type the employee number" << endl;
            cin >> employeeNumber;
            PermanentEmployee* findPerm = dyArray->search(employeeNumber);
            TemporaryEmployee* findTemp = crArray->search(employeeNumber);
            if (findTemp != nullptr) {
                crArray->deleteAfter(findTemp);
                sortedCrArray->deleteAfter(findTemp);
            }
            else if (findPerm != nullptr) {
                dyArray->deleteAfter(findPerm);
                sortedDyArray->deleteAfter(findPerm);
            }
        } else if (choose == 5){
            int empNum;
            cout << "Type the Employee Number" << endl;
            cin >> empNum;
            PermanentEmployee* findPerm = dyArray->search(empNum);
            TemporaryEmployee* findTemp = crArray->search(empNum);
            if (findTemp != nullptr) findTemp->getInfo();
            else if (findPerm != nullptr) findPerm->getInfo();
        } else if (choose == 6){
            sortedDyArray->sortNumber();
            const node *tail = sortedDyArray->getLast();
            int headCr = crArray->getHead();
            int size = crArray->getSize();
            int counter = 0;
            const node *headDy = sortedDyArray->getHead();
            bool firstTime = true;
            while (true){
                if (tail == nullptr){
                    if (counter >= size) break;
                    counter++;
                    crArray->node[headCr].tEmp->getInfo();
                    headCr = crArray->node[headCr].next;
                    continue;
                }
                if (firstTime && headDy == tail) {
                    if (counter < size) {
                        if (crArray->node[headCr].tEmp->getEmployeeNumber() < headDy->info->getEmployeeNumber()) {
                            counter++;
                            crArray->node[headCr].tEmp->getInfo();
                            headCr = crArray->node[headCr].next;
                        }
                        else {
                            headDy->info->getInfo();
                            firstTime = false;
                        }
                        continue;
                    } else{
                        headDy->info->getInfo();
                        firstTime = false;
                    }
                }
                if (counter >= size && headDy == tail) break;
                crArray->node[headCr].tEmp->getEmployeeNumber();
                if (counter >= size){
                    headDy->info->getInfo();
                    headDy = headDy->next;
                } else if (headDy == tail){
                    counter++;
                    crArray->node[headCr].tEmp->getInfo();
                    headCr = crArray->node[headCr].next;
                } else if (crArray->node[headCr].tEmp->getEmployeeNumber() < headDy->info->getEmployeeNumber()){
                    counter++;
                    crArray->node[headCr].tEmp->getInfo();
                    headCr = crArray->node[headCr].next;
                } else {
                    headDy->info->getInfo();
                    headDy = headDy->next;
                }
            }
        } else if (choose == 7){
            sortedCrArray->sortAppointment();
            const node *tail = dyArray->getLast();
            int headCr = sortedCrArray->getHead();
            int size = sortedCrArray->getSize();
            int counter = 0;
            const node *headDy = dyArray->getHead();
            bool firstTime = true;
            while (true){
                if (tail == nullptr){
                    if (counter >= size) break;
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                    continue;
                }
                if (firstTime && headDy == tail) {
                    if (counter < size) {
                        if (sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->operator<(headDy->info->getDateOfAppointment())) {
                            counter++;
                            sortedCrArray->node[headCr].tEmp->getInfo();
                            headCr = sortedCrArray->node[headCr].next;
                        }
                        else {
                            headDy->info->getInfo();
                            firstTime = false;
                        }
                    } else{
                        headDy->info->getInfo();
                        firstTime = false;
                    }
                    continue;
                }
                if (counter >= size && headDy == tail) break;
                if (counter >= size){
                    headDy->info->getInfo();
                    headDy = headDy->next;
                } else if (headDy == tail){
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                } else if (sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->operator<(headDy->info->getDateOfAppointment())){
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                } else {
                    headDy->info->getInfo();
                    headDy = headDy->next;
                }
            }
        } else if (choose == 8){
            string dt;
            cout << "Type the Date" << endl;
            cin >> dt;
            Date* d = new Date(dt);
            sortedCrArray->sortAppointmentReverse();
            const node *tail = dyArray->getLast();
            int headCr = sortedCrArray->getHead();
            int size = sortedCrArray->getSize();
            int counter = 0;
            const node *headDy = dyArray->getHead();
            bool firstTime = true;
            while (true){
                if (tail == nullptr){
                    if (counter >= size) break;
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                    continue;
                }
                if (counter >= size && !firstTime) break;
                if(counter >= size){
                    if (tail->info->getDateOfAppointment()->operator>(d)){
                        if (tail == headDy) firstTime = false;
                        tail->info->getInfo();
                        tail = tail->prev;
                        continue;
                    } else {
                        if (tail == headDy) firstTime = false;
                        tail = tail->prev;
                        continue;
                    }
                } else if (!firstTime){
                    if (sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->operator>(d)) {
                        counter++;
                        sortedCrArray->node[headCr].tEmp->getInfo();
                        headCr = sortedCrArray->node[headCr].next;
                        continue;
                    } else {
                        counter++;
                        headCr = sortedCrArray->node[headCr].next;
                        continue;
                    }
                }
                if (!tail->info->getDateOfAppointment()->operator>(d) && !sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->operator>(d)) break;
                if (!tail->info->getDateOfAppointment()->operator>(d)){
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                } else if (!sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->operator>(d)){
                    if (tail == headDy) firstTime = false;
                    tail->info->getInfo();
                    tail = tail->prev;
                } else if (tail->info->getDateOfAppointment()->operator>(d) && sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->operator>(d)){
                    if (tail->info->getDateOfAppointment()->operator>(sortedCrArray->node[headCr].tEmp->getDateOfAppointment())){
                        if (tail == headDy) firstTime = false;
                        tail->info->getInfo();
                        tail = tail->prev;
                    } else{
                        counter++;
                        sortedCrArray->node[headCr].tEmp->getInfo();
                        headCr = sortedCrArray->node[headCr].next;
                    }
                }
            }
        } else if (choose == 9){
            int year;
            cout << "Type the Year" << endl;
            cin >> year;
            sortedCrArray->sortAppointment();
            const node *tail = dyArray->getLast();
            int headCr = sortedCrArray->getHead();
            int size = sortedCrArray->getSize();
            int counter = 0;
            const node *headDy = dyArray->getHead();
            bool firstTime = true;
            while (true){
                if (tail == nullptr){
                    if (counter >= size) break;
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                    continue;
                }
                if (counter >= size && !firstTime) break;

                if(counter >= size){
                    if (headDy->info->getDateOfAppointment()->getYear() == year){
                        if (tail == headDy) firstTime = false;
                        headDy->info->getInfo();
                        headDy = headDy->next;
                        continue;
                    } else {
                        if (tail == headDy) firstTime = false;
                        headDy = headDy->next;
                        continue;
                    }
                } else if (!firstTime){
                    if (sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->getYear() == year) {
                        counter++;
                        sortedCrArray->node[headCr].tEmp->getInfo();
                        headCr = sortedCrArray->node[headCr].next;
                        continue;
                    } else {
                        counter++;
                        headCr = sortedCrArray->node[headCr].next;
                        continue;
                    }
                }
                if (headDy->info->getDateOfAppointment()->getYear() > year && sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->getYear() > year) break;
                if (headDy->info->getDateOfAppointment()->getYear() > year && sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->getYear() == year){
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                } else if (sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->getYear() > year && headDy->info->getDateOfAppointment()->getYear() == year){
                    if (tail == headDy) firstTime = false;
                    headDy->info->getInfo();
                    headDy = headDy->next;
                } else if (headDy->info->getDateOfAppointment()->getYear() == year && sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->getYear() == year){
                    if (headDy->info->getDateOfAppointment()->operator<(sortedCrArray->node[headCr].tEmp->getDateOfAppointment())){
                        if (tail == headDy) firstTime = false;
                        headDy->info->getInfo();
                        headDy = headDy->next;
                    } else{
                        counter++;
                        sortedCrArray->node[headCr].tEmp->getInfo();
                        headCr = sortedCrArray->node[headCr].next;
                    }
                } else if (headDy->info->getDateOfAppointment()->getYear() < year && sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->getYear() < year){
                    if (headDy == tail) firstTime = false;
                    headDy = headDy->next;
                    counter++;
                    headCr = sortedCrArray->node[headCr].next;
                } else if (headDy->info->getDateOfAppointment()->getYear() < year){
                    if (headDy == tail) firstTime = false;
                    headDy = headDy->next;
                } else if (sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->getYear() < year){
                    counter++;
                    headCr = sortedCrArray->node[headCr].next;
                }
            }
        } else if(choose == 10){
            string dt;
            cout << "Type the Date" << endl;
            cin >> dt;
            Date* d = new Date(dt);
            sortedDyArray->sortNumber();
            const node *tail = sortedDyArray->getLast();
            int headCr = crArray->getHead();
            int size = crArray->getSize();
            int counter = 0;
            const node *headDy = sortedDyArray->getHead();
            bool firstTime = true;
            while (true){
                if (tail == nullptr){
                    if (counter >= size) break;
                    counter++;
                    crArray->node[headCr].tEmp->getInfo();
                    headCr = crArray->node[headCr].next;
                    continue;
                }
                if (!firstTime && counter >= size) break;
                if(counter >= size){
                    if (headDy->info->getDateOfBirth()->operator<(d)){
                        if (tail == headDy) firstTime = false;
                        headDy->info->getInfo();
                        headDy = headDy->next;
                        continue;
                    } else{
                        if (tail == headDy) firstTime = false;
                        headDy = headDy->next;
                        continue;
                    }
                } else if (!firstTime){
                    if (crArray->node[headCr].tEmp->getDateOfBirth()->operator<(d)) {
                        counter++;
                        crArray->node[headCr].tEmp->getInfo();
                        headCr = crArray->node[headCr].next;
                        continue;
                    } else {
                        counter++;
                        headCr = crArray->node[headCr].next;
                        continue;
                    }
                } else if (!crArray->node[headCr].tEmp->getDateOfBirth()->operator<(d)){
                    counter++;
                    headCr = crArray->node[headCr].next;
                } else if (!headDy->info->getDateOfBirth()->operator<(d)){
                    if (tail == headDy) firstTime = false;
                    headDy = headDy->next;
                } else if (headDy->info->getEmployeeNumber() < crArray->node[headCr].tEmp->getEmployeeNumber()){
                    if (tail == headDy) firstTime = false;
                    headDy->info->getInfo();
                    headDy = headDy->next;
                } else if (headDy->info->getEmployeeNumber() >= crArray->node[headCr].tEmp->getEmployeeNumber()){
                    counter++;
                    crArray->node[headCr].tEmp->getInfo();
                    headCr = crArray->node[headCr].next;
                }
            }
        } else if (choose == 11){
            int month;
            cout << "Type the Month" << endl;
            cin >> month;
            sortedDyArray->sortNumber();
            const node *tail = sortedDyArray->getLast();
            int headCr = crArray->getHead();
            int size = crArray->getSize();
            int counter = 0;
            const node *headDy = sortedDyArray->getHead();
            bool firstTime = true;
            while (true){
                if (tail == nullptr){
                    if (counter >= size) break;
                    counter++;
                    crArray->node[headCr].tEmp->getInfo();
                    headCr = crArray->node[headCr].next;
                    continue;
                }
                if (!firstTime && counter >= size) break;
                if(counter >= size){
                    if (headDy->info->getDateOfBirth()->getMonth() == month){
                        if (tail == headDy) firstTime = false;
                        headDy->info->getInfo();
                        headDy = headDy->next;
                        continue;
                    } else {
                        if (tail == headDy) firstTime = false;
                        headDy = headDy->next;
                        continue;
                    }
                } else if (!firstTime){
                    if (crArray->node[headCr].tEmp->getDateOfBirth()->getMonth() == month) {
                        counter++;
                        crArray->node[headCr].tEmp->getInfo();
                        headCr = crArray->node[headCr].next;
                        continue;
                    } else {
                        counter++;
                        headCr = crArray->node[headCr].next;
                        continue;
                    }
                } else if (crArray->node[headCr].tEmp->getDateOfBirth()->getMonth() != month){
                    counter++;
                    headCr = crArray->node[headCr].next;
                } else if (headDy->info->getDateOfBirth()->getMonth() != month){
                    if (tail == headDy) firstTime = false;
                    headDy = headDy->next;
                } else if (headDy->info->getEmployeeNumber() < crArray->node[headCr].tEmp->getEmployeeNumber()){
                    if (tail == headDy) firstTime = false;
                    headDy->info->getInfo();
                    headDy = headDy->next;
                } else if (headDy->info->getEmployeeNumber() >= crArray->node[headCr].tEmp->getEmployeeNumber()){
                    counter++;
                    crArray->node[headCr].tEmp->getInfo();
                    headCr = crArray->node[headCr].next;
                }
            }
        } else if (choose == 12){
            string title1;
            cout << "Type the Title" << endl;
            cin >> title1;
            sortedCrArray->sortAppointmentReverse();
            const node *tail = dyArray->getLast();
            int headCr = sortedCrArray->getHead();
            int size = sortedCrArray->getSize();
            int counter = 0;
            const node *headDy = dyArray->getHead();
            bool firstTime = true;
            while (true){
                if (tail == nullptr){
                    if (counter >= size) break;
                    counter++;
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    headCr = sortedCrArray->node[headCr].next;
                    continue;
                }
                if (counter >= size && !firstTime) break;

                if(counter >= size){
                    if (tail->info->getTitle() == title1){
                        tail->info->getInfo();
                        break;
                    } else {
                        tail = tail->prev;
                        continue;
                    }
                } else if (!firstTime){
                    if (sortedCrArray->node[headCr].tEmp->getTitle() == title1) {
                        sortedCrArray->node[headCr].tEmp->getInfo();
                        break;
                    } else {
                        counter++;
                        headCr = sortedCrArray->node[headCr].next;
                        continue;
                    }
                } else if (tail->info->getTitle() != title1){
                    if (headDy == tail) firstTime = false;
                    tail = tail->prev;
                    continue;
                } else if (sortedCrArray->node[headCr].tEmp->getTitle() != title1){
                    counter++;
                    headCr = sortedCrArray->node[headCr].next;
                    continue;
                } if (sortedCrArray->node[headCr].tEmp->getDateOfAppointment()->operator>(tail->info->getDateOfAppointment())){
                    sortedCrArray->node[headCr].tEmp->getInfo();
                    break;
                } else {
                    if (tail == headDy)
                        tail->info->getInfo();
                    break;
                }
            }
        } else continue;
    }
}