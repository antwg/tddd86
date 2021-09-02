// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

using namespace std;

void ShowStartMessage(){
    cout << "Welcome to the TDDD86 Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "  - A cell with 1 or fewer neighbours dies." << endl;
    cout << "  - Locations with 2 neighbours remain stable." << endl;
    cout << "  - Locations with 3 neighbours will create life." << endl;
    cout << "  - A cell with 4 or more neighbours dies." << endl;
    cout << endl;
}

string GetFileName(){
    string fileName;
    cout << "Grid input file name? ";
    cin >> fileName;
    return fileName;
}

Grid<string> CreateGridFromFile(string fileName){
    int numRows, numCols, currLine = 0, currGridRow = 0;
    string line;
    ifstream file(fileName);
    Grid<string> grid = Grid<string>();

    while (getline(file, line) && !line.empty()){
        if(currLine == 0){                            // First line contains number of rows
            numRows = stoi(line);
        }
        else if(currLine == 1){                       // Second line contains number of columns
            numCols = stoi(line);
            grid.resize(numRows, numCols);
        }
        else {                                        // Start of grid values
            for (int col = 0; col < numCols; col++){
                grid[currGridRow][col] = line[col];   // Insert values into grid
            }
        currGridRow++;
        }
    currLine++;                                       // Proceed to next line in file
    }
    file.close();
    return grid;
}

void PrintGrid(Grid<string> grid){
    for (int row = 0; row < grid.numRows(); row++){
        for (int col = 0; col < grid.numCols(); col++){
            cout << grid.get(row, col);
        }
        cout << endl;
    }
}

int main() {
    ShowStartMessage();
    string fileName = GetFileName();
    Grid<string> grid = CreateGridFromFile(fileName);
    PrintGrid(grid);
    return 0;
}
