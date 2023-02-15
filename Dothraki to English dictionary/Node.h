#ifndef UNTITLED2_NODE_H
#define UNTITLED2_NODE_H
#include <iostream>
using namespace std;

class Node {
public:
    Node();

    const string &getValue() const;

    void setValue(const string &value);

    Node* next[26]{};

private:
    string value;
};


#endif
