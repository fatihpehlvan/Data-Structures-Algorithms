#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
stack<string>* output;

void PrintStack(string *out)
{
    // If stack is empty then return
    if (output->empty()){
        return;
    }

    string x = output->top();

    // Pop the top element of the stack
    output->pop();

    // Recursively call the function PrintStack
    PrintStack(out);

    // Print the stack element starting
    // from the bottom
    out->append(x + ",");

    // Push the same element onto the stack
    // to preserve the order
    output->push(x);
}
// my print function
void Print(bool dollar, string* out){
    cout << *out;
    auto *out1 = new string;
    // print $ symbol if Z includes $
    if (dollar){
        out1->append("&,");
    }
    PrintStack(out1);
    // print except last ,
    cout << out1->substr(0,out1->size()-1);
    cout << endl;
}

int main(int argc, char *argv[]) {
    // define variables
    bool dollar = false;
    vector<string> stateNames;
    vector<string> finals;
    vector<string> alphabet;
    vector<string> stackAlphabet;
    vector<vector<string>> states;
    vector<vector<string>> forEValues;
    string initialStep;
    // my output file
    freopen(argv[3],"w",stdout);
    ///////    read dpda file ///////////
    fstream myFile;
    // open DPDA file
    myFile.open(argv[1], ios::in);
    if (myFile.is_open()) {
        string line;
        while (getline(myFile, line)) {
            string add;
            bool colon = false;
            if (line.substr(0, 1) == "Q") {
                bool bigger = false;
                bool paranthesis = false;
                bool squareBrackets = false;
                for (char i: line) {
                    // continue before colon symbols.
                    if (i == ':')
                        colon = true;
                    // this is for initial and final steps
                    else if (i == '>')
                        bigger = true;
                    else if (bigger) {
                        if (i == ' ') continue;
                        // this is for initial step
                        else if (i == '(') {
                            paranthesis = true;
                            add = "";
                        } else if (i == ')') {
                            paranthesis = false;
                            initialStep = add;
                            add = "";
                        } else if (paranthesis) add.append(string(1, i));
                        // this is for determine final steps
                        else if (i == '[') squareBrackets = true;
                        else if (i == ']') {
                            squareBrackets = false;
                            finals.push_back(add);
                            add = "";
                        } else if (squareBrackets) add.append(string(1, i));
                    } else if (!colon) continue;
                    else if ((i == ',' || i == ' ')) {
                        stateNames.push_back(add);
                        add = "";
                    } else add.append(string(1, i));
                }
            }
            // this is for alphabet "A"
            else if (line.substr(0, 1) == "A") {
                for (char i: line) {
                    if (i == ':')
                        colon = true;
                    else if (colon) {
                        if (i == ',') {
                            alphabet.push_back(add);
                            add = "";
                        } else add.append(string(1, i));
                    }
                }
                alphabet.push_back(add);
            }
            // This is for alphabet "Z"
            else if (line.substr(0, 1) == "Z") {
                for (char i: line) {
                    if (i == ':')
                        colon = true;
                    else if (colon) {
                        if (i == ',') {
                            if (add == "$") dollar = true;
                            stackAlphabet.push_back(add);
                            add = "";
                        } else add.append(string(1, i));
                    }
                }
                if (add == "$") dollar = true;
                stackAlphabet.push_back(add);
            }
            // This for states "T"
            else if (line.substr(0, 1) == "T") {
                vector<string> myVec;
                for (char i: line) {
                    if (i == ':')
                        colon = true;
                    else if (colon) {
                        if (i == ',') {
                            myVec.push_back(add);
                            add = "";
                        } else add.append(string(1, i));
                    }
                }
                myVec.push_back(add);
                if (myVec.size() != 5) {
                    cout << "Error [1]:DPDA description is invalid!" << endl;
                    exit(0);
                }
                // this is for states which includes "e" in first element
                if (myVec[1] == "e") forEValues.push_back(myVec);
                // this is for states which does not include "e" in first element
                else states.push_back(myVec);
            }
        }
        myFile.close();
    }
    // merge states
    for (const vector<string> &i: forEValues)
        states.push_back(i);
    //////// read dpda input file ////////////

    vector<vector<string>> inputVector;
    // open input file
    myFile.open(argv[2], ios::in);
    if (myFile.is_open()) {
        string line;
        while (getline(myFile, line)) {
            string add;
            vector<string> addingVec;
            // this is split according to ","
            for (char i: line) {
                if (i == ',') {
                    addingVec.push_back(add);
                    add = "";
                } else add.append(string(1, i));
            }
            if (!add.empty()) {
                addingVec.push_back(add);
            }
            addingVec.push_back("e");
            inputVector.push_back(addingVec);
        }
    }
    // determine if there is an error in DPDA file
    bool invalid = false;
    for (const vector<string> &check: states) {
        if (check.size() != 5) {
            invalid = true;
            break;
        }
        if (find(stateNames.begin(), stateNames.end(), check[0]) == stateNames.end() ||
            find(stateNames.begin(), stateNames.end(), check[3]) == stateNames.end() ||
            (check[1] != "e" && find(alphabet.begin(), alphabet.end(), check[1]) == alphabet.end()) ||
            (check[2] != "e" && find(stackAlphabet.begin(), stackAlphabet.end(), check[2]) == stackAlphabet.end()) ||
            (check[4] != "e" && find(stackAlphabet.begin(), stackAlphabet.end(), check[4]) == stackAlphabet.end())) {

            invalid = true;
            break;
        }
        if (find(stateNames.begin(), stateNames.end(), initialStep) == stateNames.end()){
            invalid = true;
            break;
        }
        for (const string& finalStates : finals){
            if (find(stateNames.begin(), stateNames.end(), finalStates) == stateNames.end()){
                invalid = true;
                break;
            }
        }
    }
    // my error message
    if (invalid) {
        cout << "Error [1]:DPDA description is invalid!" << endl;
        exit(1);
    }
    /////////////// Apply Rules //////////////////

    for (const vector<string> &inputLines: inputVector) {
        string currStep = initialStep;
        output = new stack<string>;
        int count = 0;
        string ch = "";
        bool secondBreak;
        for (const string& inputString: inputLines) {
            secondBreak = false;
            count++;
            bool willBeBroken = false;
            while (true) {
                bool check = true;
                for (const vector<string> &stateLines: states) {
                    string out = stateLines[0] + "," + stateLines[1] + "," + stateLines[2] + " => " + stateLines[3] + "," + stateLines[4] + " [STACK]:";
                    if (stateLines[0] == currStep) {
                        // check the stack empty or not
                        if (output->empty()) {
                            // check if the first element of state is proper
                            if (stateLines[1] != inputString && stateLines[1] != "e") continue;
                            check = false;
                            // this is for removing element from empty stack
                            if (stateLines[2] != "e" && stateLines[4] == "e" && stateLines[2] != "$") {
                                cout << "Error [1]:DPDA description is invalid!" << endl;
                                return 62;
                            }
                            // this is my next step
                            currStep = stateLines[3];
                            // adding new element and print them
                            if (stateLines[4] != "e" && stateLines[2] == "e") {
                                if (stateLines[4] != "$")
                                    output->push(stateLines[4]);
                                if (stateLines[1] == "e") {
                                    currStep = stateLines[3];
                                    Print(dollar, &out);
                                    break;
                                } else if (stateLines[1] == inputString) {
                                    willBeBroken = true;
                                    Print(dollar, &out);
                                    break;
                                }
                            }
                            // if second and 4th element equal to "e" do nothing print normal stack
                            else if (stateLines[2] == "e" && stateLines[4] == "e") {
                                Print(dollar, &out);
                                break;
                            } else if (stateLines[2] == "$") Print(dollar, &out);
                        }
                        // this is for nonempty stack
                        else {
                            // check if the first element of state is proper
                            if (stateLines[1] != inputString && stateLines[1] != "e" || (stateLines[2] != "e" && stateLines[2] != output->top())) continue;
                            // this is my next step
                            currStep = stateLines[3];
                            check = false;
                            // if input was used, the program should go next step so that change the boolen value.
                            if (stateLines[1] == inputString) {
                                willBeBroken = true;
                            }
                            if (stateLines[2] == "e" && stateLines[4] == "e") {
                                Print(dollar, &out);
                                break;
                            }
                            // if second and 4th element equal to "e" do nothing print normal stack
                            else if (stateLines[2] == "e" && stateLines[4] != "e") {
                                if (stateLines[4] != "$")
                                    output->push(stateLines[4]);
                                Print(dollar, &out);
                                break;
                            }
                            // adding new element and print them
                            else if (stateLines[2] == output->top() && stateLines[4] == "e") {
                                if (stateLines[4] != "$")
                                    output->pop();
                                Print(dollar, &out);
                                break;
                            }
                            // if second and 4th element equal to "e" do nothing print normal stack
                            else if (stateLines[2] == output->top() && stateLines[4] != "e") {
                                Print(dollar, &out);
                                break;
                            }
                        }
                    }
                }
                // check reject situation
                if (check && !output->empty()){
                    willBeBroken = true;
                    secondBreak = true;
                    cout << "REJECT" << endl;
                }
                if (count  == inputLines.size()){
                    willBeBroken = false;
                    if (ch == currStep){
                        willBeBroken = true;
                    } else ch = currStep;
                }
                if (willBeBroken) break;
            }
            if (secondBreak) break;
        }
        // check accept situation
        if (!secondBreak) cout << "ACCEPT" << endl;
        cout << endl;
    }
}