#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

set<string> neighbours;

// This function removes white spaces at the end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(),
                    not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// This function returns double pointer and set inputList according to input
int** read (const string& fileDirectory, int* size, vector<string>&inputList, bool second){
    fstream inputFile;
    // initialize 2d array
    int** board = nullptr;
    // read the file
    inputFile.open(fileDirectory, ios::in);
    if (inputFile.is_open())
    {
        string line;
        int index = -1;

        while (getline(inputFile, line))
        {
            line = rtrim(line);
            index++;
            if (index == 0)
            {
                *size = stoi(line);
                board = new int*[*size];
                continue;
            }
            if (index <= *size && second){
                board[index-1] = new int[*size];
                int i = 0;
                string add;
                for (char k : line){
                    if(k == ' '){
                        board[index-1][i] = stoi(add);
                        add.clear();
                        i++;
                        continue;
                    }
                    else{
                        add.push_back(k);
                    }
                }
                board[index-1][i] = stoi(add);
                continue;
            }
            inputList.push_back(line);

        }
        if (!second){
            for (int i = 0; i < *size; i++) {
                board[i] = new int[*size];
                for (int k = 0; k < *size; k++) {
                    board[i][k] = 0;
                }
            }
        }
        inputFile.close();
    }
    return board;
}

// This function checks a set if the set contains a special string.
bool contains(set<string> s, const string& str)
{
    return s.find(str) != s.end();
}

// This function checks neighbours of a special location and then insert the locations in a set as a string.
void checkNeighbour(int** grid, int row, int column, int point, int size)
{
    neighbours.insert(to_string(row).append(",").append(to_string(column)));
    if (row != 0)
    {
        if (point == grid[row - 1][column] && !contains(neighbours, to_string(row - 1).append(",").append(to_string(column))))
        {
            checkNeighbour(grid, row - 1, column, point, size);
        }
    }
    if (row != size - 1)
    {
        if (point == grid[row + 1][column] && !contains(neighbours, to_string(row + 1).append(",").append(to_string(column))))
        {
            checkNeighbour(grid, row + 1, column, point, size);
        }
    }
    if (column != 0)
    {
        if (point == grid[row][column - 1] && !contains(neighbours, to_string(row).append(",").append(to_string(column - 1))))
        {
            checkNeighbour(grid, row, column - 1, point, size);
        }
    }
    if (column != size - 1)
    {
        if (point == grid[row][column + 1] && !contains(neighbours, to_string(row).append(",").append(to_string(column + 1))))
        {
            checkNeighbour(grid, row, column + 1, point, size);
        }
    }
}

int main(int argc, char *argv[]) {
    freopen(argv[3],"w",stdout);
    int size;
    int* sizePtr = &size;
    vector<string> inputList;
    string fileDirectory = argv[1];
    int** grid = read(fileDirectory, sizePtr, inputList, false);
    int pass2elements = 0;
    for (string line : inputList)
    {
        int index = 0;
        int count = 0;
        int point = 0;
        int row = 0;
        int column = 0;
        for (int i = 0; i < line.size(); i++)
        {
            // this is my split step
            if (line.at(i) == ' ')
            {
                switch (count)
                {
                    case 0:
                        point = stoi(line.substr(index));
                        index = i + 1;
                        count++;
                        break;
                        case 1:
                            row = stoi(line.substr(index));
                            count++;
                            index = i + 1;
                            column = stoi(line.substr(index));
                            break;
                            default:
                                break;
                }
            }
        }
        grid[row][column] = point;

        // this conditon pass first and second step. Because they can't make a group
        if (pass2elements < 2)
        {
            pass2elements++;
            continue;
        }
        neighbours.clear();
        //neighbours.insert(to_string(row).append(",").append(to_string(column)));
        checkNeighbour(grid, row,column,point, size);
        while (neighbours.size() >=3){
            // this loop make the neidhbours = 0
            for (const auto& willBeDeleted : neighbours){
                bool comma = false;
                string willBeDeletedRow;
                string willBeDeletedColumn;
                for (char i : willBeDeleted){
                    // this is my split function according to comma
                    if(i == ','){
                        comma = true;
                        continue;
                    }
                    if(comma){
                        willBeDeletedColumn.push_back(i);
                    } else willBeDeletedRow.push_back(i);
                }
                grid[stoi(willBeDeletedRow)][stoi(willBeDeletedColumn)] = 0;
            }
            neighbours.clear();
            // increase last element 1
            point++;
            grid [row][column] = point;
            checkNeighbour(grid, row,column,point, size);
        }
    }
    // print the last board
    cout << "PART 1:" << endl;
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << grid[i][j];
            if (j != size - 1)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    ////////////////// PART 2 ///////////////////////

    // set the variables
    inputList.clear();
    fileDirectory = argv[2];
    int** secondBoard = read(fileDirectory, sizePtr, inputList, true);
    int totalPoint = 0;

    // plant the bomb on proper location
    for (string bombsLocations : inputList){
        int point;
        int row = 0;
        int column = 0;
        for (int i = 0; i < bombsLocations.size(); i++)
        {
            // determine bomb's row and column
            if (bombsLocations.at(i) == ' ')
            {
                row = stoi(bombsLocations.substr(0,i));
                column = stoi(bombsLocations.substr(i+1));
            }
        }
        point = secondBoard[row][column];
        totalPoint += point;
        secondBoard[row][column] = 0;
        // set 0 when same , column and diagonal equals to the point
        for (int i = 0; i < size; i++){
            if (secondBoard[i][column] == point){
                secondBoard[i][column] = 0;
                totalPoint += point;
            }
            if (secondBoard[row][i] == point){
                secondBoard[row][i] = 0;
                totalPoint += point;
            }
            if(!(row - i < 0 || column + i >= size)){
                if(secondBoard[row - i][column + i] == point){
                    secondBoard[row-i][column+i] = 0;
                    totalPoint += point;
                }
            }
            if(!(row - i < 0 || column - i < 0)){
                if(secondBoard[row - i][column - i] == point){
                    secondBoard[row - i][column - i] = 0;
                    totalPoint += point;
                }
            }
            if(!(row + i >= size || column + i >= size)){
                if(secondBoard[row + i][column + i] == point){
                    secondBoard[row + i][column + i] = 0;
                    totalPoint += point;
                }
            }
            if(!(row + i >= size || column - i < 0)){
                if(secondBoard[row + i][column - i] == point){
                    secondBoard[row + i][column - i] = 0;
                    totalPoint += point;
                }
            }
        }
    }

    // print the second board
    cout << "PART 2:" << endl;
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << secondBoard[i][j];
            if (j != size - 1)
                cout << " ";
        }
            cout << endl;
	
    }
    cout << "Final Point: " << totalPoint << "p";
}