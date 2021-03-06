// Plays the game of life
// Imports a text document and creates a grid from the information given in
// the document. The user can then play the game by either ticking by 1 generation
// or 15 in a row.

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

void getFileName(string& fileName){
    cout << "Grid input file name? ";
    cin >> fileName;
}

void getGridFromFile(const string fileName, Grid<string>& grid){
    int currLine = 0;
    int numRows;
    int numCols;
    string line;
    ifstream file(fileName);

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
                int row = currLine - 2;               // 2 lines for number of rows and cols
                grid[row][col] = line[col];           // Insert values into grid
            }
        }
    currLine++;                                       // Proceed to next line in file
    }
    file.close();
}

void printGrid(const Grid<string>& grid){
    for (int row = 0; row < grid.numRows(); row++){
        for (int col = 0; col < grid.numCols(); col++){
            cout << grid.get(row, col);
        }
        cout << endl;
    }
}

void printOptions(){
    cout << "a)nimate, t)ick, q)uit?";
}

int countNeighbors(const Grid<string>& grid, const int row, const int col){
    int total = 0;
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            int currRow = row + i;
            int currCol = col + j;
            if (grid.inBounds(currRow, currCol)){
                if (grid.get(currRow, currCol) == "X"){
                    total++;
                }
            }
        }
    }
    if (grid.get(row, col) == "X"){
        total--;
    }
    return total;
}

void tick(Grid<string>& grid){
    Grid<string> nextGen = grid;
    for (int row = 0; row < grid.numRows(); row++){
        for (int col = 0; col < grid.numCols(); col++){
            int neighbors = countNeighbors(grid, row, col);

            if (neighbors < 2){         // Starving
                nextGen[row][col] = "-";
            } else if (neighbors == 2){ // Stable
                // Do nothing
            } else if (neighbors == 3){ // Growing
                nextGen[row][col] = "X";
            } else {                    // Overpopulated
                nextGen[row][col] = "-";
            }
        }
    }
    grid = nextGen;
    printGrid(grid);
}

void animate(Grid<string>& grid){
    for (int i = 0; i < 50; i++){
        clearConsole();
        tick(grid);
        pause(100);
    }
}

int main() {
    Grid<string> grid;
    ShowStartMessage();
    string fileName;
    getFileName(fileName);
    getGridFromFile(fileName, grid);

    printGrid(grid);
    printOptions();

    char nextAction;
    while (cin >> nextAction){
        if (nextAction == 't'){
            tick(grid);
            printOptions();
        }
        else if (nextAction == 'a'){
            animate(grid);
            printOptions();
        }
        else if (nextAction == 'q'){
            break;
        }
    }
    return 0;

}
