#ifndef AS2_2_CIRCULARARRAYLINKEDLIST_H
#define AS2_2_CIRCULARARRAYLINKEDLIST_H
#include <iostream>
#include "TemporaryEmployee.h"
using namespace std;

class CircularArrayLinkedList {
private:
    struct nodetype {
        TemporaryEmployee* tEmp;
        int next;
    };
    int avail = 0;
    int head = -1;
    int last = -1;
    int getNode();
    void freeNode(int p);
    int size = 0;
public:
    CircularArrayLinkedList();
    void insertAfter (TemporaryEmployee* element);
    void deleteAfter(TemporaryEmployee* element);
    TemporaryEmployee* search(int element);
    void sortAppointment();
    void sortAppointmentReverse();
    struct nodetype node[20];
    int getHead() const;
    int getSize() const;
};
#endif //AS2_2_CIRCULARARRAYLINKEDLIST_H
