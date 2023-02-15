#include "Node.h"

Node::Node() {
    // make all values null
    for (auto & i : next) {
        i = nullptr;
    }
    value = "";
}
// getter gunction
const string &Node::getValue() const {
    return value;
}
// setter function
void Node::setValue(const string &value) {
    Node::value = value;
}


