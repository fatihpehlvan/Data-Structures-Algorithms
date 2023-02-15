#include "DoubleDynamicLinkedList.h"

DoubleDynamicLinkedList::DoubleDynamicLinkedList() = default;

// getNode to delete pointer.
NODEPTR DoubleDynamicLinkedList::getNode() {
    NODEPTR p;
    p = new node;
    return p;
}
// freeNode function to make free which is deleted.
void DoubleDynamicLinkedList::freeNode(NODEPTR p)
{
    delete p;
}
// insertAfter add element in the linked-list by old to new by appointment date.
void DoubleDynamicLinkedList::insertAfter(PermanentEmployee* x)
{
    size++;
    NODEPTR q;
    q = DoubleDynamicLinkedList::getNode();
    q->info = x;
    if(head == nullptr){
        head = last = q;
        return;
    }
    if (head == last){
        if(head->info->getDateOfAppointment()->operator<(x->getDateOfAppointment())){
            head->next = q;
            q->prev = head;
            last = q;
            return;
        } else{
            q->next = head;
            head->prev = q;
            head = q;
        }
    }
    NODEPTR search = head;
    while (search != last && !x->getDateOfAppointment()->operator<(search->info->getDateOfAppointment())){
        search = search->next;
    }

    if (search == last && !(x->getDateOfAppointment()->operator<(search->info->getDateOfAppointment()))){
        last->next = q;
        q->prev = last;
        last = q;
        return;
    }
    else if (search == last && !(search->info->getDateOfAppointment()->operator<(x->getDateOfAppointment()))){
        search->prev->next = q;
        q->prev = search->prev;
        q->next = search;
        search->prev = q;
        return;
    }
    else if (head == search){
        head->prev = q;
        q->next = head;
        head = q;
        return;
    }
    search->prev->next = q;
    q->next = search;
    q->prev = search->prev;
    search->prev = q;
}
// deleteAfter remove the element which you choose.
void DoubleDynamicLinkedList::deleteAfter(PermanentEmployee* element)
{
    size--;
    NODEPTR find = head;
    while (find->info != element){
        find = find->next;
        if (find == head) break;
    }
    if (size == 0){
        freeNode(head);
        head = nullptr;
        last = nullptr;
        return;
    }
    if (find == last){
        last = last->prev;
        last->next = nullptr;
    }else if (head !=find) {
        find->prev->next = find->next;
        find->next->prev = find->prev;
    } else{
        head = head->next;
        head->prev = nullptr;
    }
    freeNode(find);
}
// search function searches an element according to permanentEmployeeNumber.
PermanentEmployee* DoubleDynamicLinkedList::search(int element) {
    NODEPTR index = head;
    if (size == 0) return nullptr;
    while (index != last){
        if (element == index->info->getEmployeeNumber())
            return index->info;
        index = index->next;
    }
    if (element == index->info->getEmployeeNumber())
        return index->info;
    return nullptr;
}
// sortNumber sorts the list according to employee number ascending order.
void DoubleDynamicLinkedList::sortNumber() {
    node* cur1 = head;
    node* cur2 = head;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (cur1->info->getEmployeeNumber() < cur2->info->getEmployeeNumber()) {
                PermanentEmployee* temp = cur1->info;
                cur1->info = cur2->info;
                cur2->info = temp;

            }
            cur2 = cur2->next;
        }
        cur2 = head;
        cur1 = head->next;
        for (int k = 0; k < i; k++) {
            cur1 = cur1->next;
        }
    }
}
// getHead returns to head NODEPTR.
const node *DoubleDynamicLinkedList::getHead() const {
    return head;
}
// getLast returns the last NODEPTR.
const node *DoubleDynamicLinkedList::getLast() const {
    return last;
}
