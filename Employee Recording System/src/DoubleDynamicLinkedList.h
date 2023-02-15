#ifndef AS2_2_DOUBLEDYNAMICLINKEDLIST_H
#define AS2_2_DOUBLEDYNAMICLINKEDLIST_H
#include <iostream>
#include "PermanentEmployee.h"
using namespace std;
struct node {
    PermanentEmployee* info;
    struct node *next;
    struct node *prev;
};
typedef struct node* NODEPTR;
class DoubleDynamicLinkedList {
private:
    int size = 0;
    NODEPTR head = nullptr;
    NODEPTR last = nullptr;
    static NODEPTR getNode();
    static void freeNode(NODEPTR p);
public:
    DoubleDynamicLinkedList();
    void insertAfter (PermanentEmployee* element);

    const node *getHead() const;

    const node *getLast() const;

    void deleteAfter(PermanentEmployee *element);

    PermanentEmployee *search(int element);
    void sortNumber();
};




#endif //AS2_2_DOUBLEDYNAMICLINKEDLIST_H
