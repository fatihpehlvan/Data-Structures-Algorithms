#include "Trie.h"

Trie::Trie() {
    root = new Node;
}
// returns number of childs
int Trie::anotherChild(Node* node) {
    int count = 0;
    for (auto child : node->next){
        if (child != nullptr) count++;
    }
    return count;
}



void Trie::insert(string key, const string& value) {
    // tmp goes to proper area starting with root.
    Node* tmp = root;
    int size = key.size();
    string tmpKey = key;
    for (int i = 0; i < size; i++) {
        // create new node
        if (tmp->next[int(key.at(0))-97] == nullptr)
            tmp->next[int(key.at(0))-97] = new Node;
        tmp = tmp->next[int(key.at(0))-97];
        key = key.substr(1, key.size()-1);
        // apply the pdf rules
        if (key.empty()){
            if (tmp->getValue() == value){
                cout << "\"" <<tmpKey << "\"" << " already exist" << endl;
                return;
            } else if (tmp->getValue().empty()){
                cout<< "\"" << tmpKey << "\"" << " was added" << endl;
            } else{
                cout<< "\"" << tmpKey << "\"" << " was updated" << endl;
            }
            tmp->setValue(value);
            return;
        }
    }
}
// this function returns true if there is an element in the tree
bool Trie::search(string key) {
    Node* tmp = root;
    int size = key.size();
    if (tmp->next[int(key.at(0)) - 97] == nullptr){
        cout << "\"no record\"" << endl;
        return false;
    }

    for (int i = 0; i < size; i++) {
        tmp = tmp->next[int(key.at(0))-97];
        key = key.erase(0,1);
        // check incorrect or not
        if (tmp == nullptr){
            cout << "\"incorrect Dothraki word\"" << endl;
            return false;
        }
        if (key.empty()){
            // check there is a value at the end
            if (tmp->getValue().empty()){
                cout << "\"not enough Dothraki word\"" << endl;
                return false;
            } else{
                cout << "\"The English equivalent is " << tmp->getValue() << "\"" << endl;
                return true;
            }
        }
    }
    return true;
}
// this function remove element from trie
void Trie::remove(string key) {
    Node* tmp = Trie::root;
    string tmpKey = key;
    int size = key.size();
    stack<Node*> willBeDeleted;
    stack<int> index;
    // check first node array
    if (tmp->next[int(key.at(0)) - 97] == nullptr){
        cout << "\"no record\"" << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        tmp = tmp->next[int(key.at(0))-97];
        index.push((key.at(0))-97);
        willBeDeleted.push(tmp);
        key.erase(key.begin());
        // check incorrect or not
        if (tmp == nullptr){
            cout << "\"incorrect Dothraki word\"" << endl;
            return;
        }
        if (key.empty()){
            // check is there a value
            if (tmp->getValue().empty()){
                cout << "\"not enough Dothraki word\"" << endl;
                return;
            }
        }
    }
    tmp->setValue("");
    cout<< "\"" << tmpKey << "\"" << " deletion is successful" << endl;
    while (!willBeDeleted.empty()){
        tmp = willBeDeleted.top();
        if (anotherChild(tmp) != 0 || !tmp->getValue().empty())break;
        delete tmp;
        tmp = NULL;
        willBeDeleted.pop();
        if (willBeDeleted.empty()){
            // make null proper node
            root->next[index.top()] = nullptr;
            index.pop();
        } else{
            // make prev array null in proper index
            willBeDeleted.top()->next[index.top()] = nullptr;
            index.pop();
        }
    }
}

void Trie::list(Node *child, char *stri, int level, string st) {

    if (anotherChild(child) == 0 || !child->getValue().empty())
    {
        stri[level] = '\0';
        st = stri;
        // print elements
        cout << "-" << st << "(" << child->getValue() << ")" << endl;
    }
    int i;
    for (i = 0; i < 26; i++)
    {
        // find not null area.
        if (child->next[i])
        {
            stri[level] = i + 'a';
            st = stri;
            list(child->next[i], stri, level + 1, st);
        }
    }

}

void Trie::list() {
    char * ch = new char;
    string st = "";

    list(root, ch, 0, st);
}