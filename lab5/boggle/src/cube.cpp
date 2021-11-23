/*
 * antwe841
 * bensu844
 *
 * The cube class stores information about a boggle cube such as
 * the letters on the sides of a boggle cube, which face is up,
 * and if the cube has been visited by the search algorithm.
 */

#include "cube.h"
#include "random.h"

Cube::Cube(){}

Cube::Cube(const string& letters){
    this->letters = letters;
    this->visited = false;
    shake();
}

void Cube::shake(){
    this->topLetter = letters[randomInteger(0, letters.size() - 1)];
}

string Cube::getTopLetter(){
    return topLetter;
}

void Cube::forceTopLetter(char letter){
    this->topLetter = string(1, letter);
}

bool Cube::isVisited(){
    return visited;
}

void Cube::setVisited(const bool choice){
    this->visited = choice;
}
