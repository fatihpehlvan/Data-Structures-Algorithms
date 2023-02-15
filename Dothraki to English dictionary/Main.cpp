#include <iostream>
#include <fstream>
#include <vector>
#include "Trie.h"
using namespace std;


int main(int argc, char *argv[]) {
    vector<vector<string>> inputFile;
    fstream myFile;
    // open file
    myFile.open(argv[1], ios::in);
    freopen(argv[2],"w",stdout);
    if (myFile.is_open()) {
        string line;
        while (getline(myFile, line)) {
            string add;
            vector<string> tmp;
            for (char i : line){
                // split lines according to ( ) ,
                if (i == '(' || i == ')' || i == ','){
                    tmp.push_back(add);
                    add = "";
                    continue;
                } else {
                    add.append(string(1,i));
                }
            }
            if (tmp.empty()){
                tmp.push_back(add);
            }
            // add lines in 2d vector
            inputFile.push_back(tmp);
        }
        myFile.close();
    }
    Trie myTrie;
    // follow rules
    for (const vector<string>& lines : inputFile){
        if (lines[0] == "insert"){
            myTrie.insert(lines[1], lines[2]);
        }else if (lines[0] == "search"){
            myTrie.search(lines[1]);
        }else if (lines[0] == "delete"){
            myTrie.remove(lines[1]);
        } else myTrie.list();
    }

}