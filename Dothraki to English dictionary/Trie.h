#ifndef UNTITLED2_TRIE_H
#define UNTITLED2_TRIE_H
#include "Node.h"
#include <queue>
#include <stack>

using namespace std;

class Trie {
public:
    Trie();
    void insert(string key,const string& value);
    bool search(string key);
    void remove(string key);
    void list();

private:
    Node* root;
    static int anotherChild(Node* root);
    void list(Node *child, char *stri, int level, string st);
};


#endif
