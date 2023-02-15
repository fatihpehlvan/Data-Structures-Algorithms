#include "CircularArrayLinkedList.h"

CircularArrayLinkedList::CircularArrayLinkedList() {
    for(int i=0;i<19;i++) {
        node[i].next = i + 1;
        node[i].tEmp = nullptr;
    }
    node[19].next = 0;
    node[19].tEmp = nullptr;
}
// getNode to take a free area in the array.
int CircularArrayLinkedList::getNode() {
    int p;
    p = avail;
    avail = node[avail].next;
    return p;
}
// freeNode function to make free which is deleted.
void CircularArrayLinkedList::freeNode(int p) {
    node[p].next = avail;
    avail = p;
}
// insertAfter add element in the linked-list by ascending order by employee number.
void CircularArrayLinkedList::insertAfter(TemporaryEmployee* element) {
    size++;
    int q;
    q = getNode();
    node[q].tEmp = element;
    if (last == -1) {
        head = q;
        last = q;
        node[q].next = head;
        return;
    }
    int index = head;
    int prev = head;
    while (node[index].tEmp->getEmployeeNumber() < element->getEmployeeNumber() && node[index].next != head){
        prev = index;
        index = node[index].next;
    }
    if(head == node[index].next && node[last].tEmp->getEmployeeNumber() < element->getEmployeeNumber()){
        node[last].next = q;
        last = q;
        node[last].next = head;
        return;
    }
    if (head == index){
        node[q].next = head;
        head = q;
        node[last].next = head;
        return;
    }
    node[prev].next = q;
    node[q].next = index;


}
// deleteAfter remove the element which you choose.
void CircularArrayLinkedList::deleteAfter(TemporaryEmployee* element) {
    size--;
    int index = head;
    int prev = head;
    while (node[index].tEmp != element){
        prev = index;
        index = node[index].next;
        if (index == head) break;
    }

    if (index == head){
        if (node[index].tEmp == element){
            int tmp = node[head].next;
            node[head].tEmp = nullptr;
            freeNode(head);
            head = tmp;
            node[last].next = head;
            return;
        } else if (last == head) {
            int tmp = node[head].next;
            node[head].tEmp = nullptr;
            freeNode(head);
            head = tmp;
        }
        node[last].tEmp = nullptr;
        freeNode(last);
        last = prev;
        node[prev].next = head;
        return;
    }
    if (index == last){
        last = prev;
        node[last].next = head;
        node[index].tEmp = nullptr;
    } else {
        node[prev].next = node[index].next;
        node[index].tEmp = nullptr;
    }
    freeNode(index);
}
// search function searchs element according to temproryEmployeeNumber.
TemporaryEmployee* CircularArrayLinkedList::search(int element) {
    int index = head;
    if (size == 0) return nullptr;
    while (node[index].next != head){
        if (element == node[index].tEmp->getEmployeeNumber())
            return node[index].tEmp;
        index = node[index].next;
    }
    if (element == node[index].tEmp->getEmployeeNumber())
        return node[index].tEmp;;
    return nullptr;
}
// sortAppointment sorts the list according to appointment date old to new.
void CircularArrayLinkedList::sortAppointment() {
    int cur1 = head;
    int cur2 = head;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (node[cur1].tEmp->getDateOfAppointment()->operator<(node[cur2].tEmp->getDateOfAppointment())) {
                TemporaryEmployee *temp = node[cur1].tEmp;
                node[cur1].tEmp = node[cur2].tEmp;
                node[cur2].tEmp = temp;

            }
            cur2 = node[cur2].next;
        }
        cur2 = head;
        cur1 = node[head].next;
        for (int k = 0; k < i; k++) {
            cur1 = node[cur1].next;
        }
    }
}
// sortAppointmentReverse sorts the list according to appointments new to old.
void CircularArrayLinkedList::sortAppointmentReverse(){
    int cur1 = head;
    int cur2 = head;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (node[cur1].tEmp->getDateOfAppointment()->operator>(node[cur2].tEmp->getDateOfAppointment())) {
                TemporaryEmployee *temp = node[cur1].tEmp;
                node[cur1].tEmp = node[cur2].tEmp;
                node[cur2].tEmp = temp;

            }
            cur2 = node[cur2].next;
        }
        cur2 = head;
        cur1 = node[head].next;
        for (int k = 0; k < i; k++) {
            cur1 = node[cur1].next;
        }
    }
}
// getHead returns to head index.
int CircularArrayLinkedList::getHead() const {
    return head;
}
// getSize returns the size.
int CircularArrayLinkedList::getSize() const {
    return size;
}

