#include "cube.h"
#include "random.h"

Cube::Cube(const string& letters){
    this->letters = letters;
    this->topLetter = letters[randomInteger(0, letters.size())];
    this->visited = false;
}

void Cube::shake(){
    this->topLetter = letters[randomInteger(0, letters.size())];
}

char Cube::getTopLetter(){
    return topLetter;
}

bool Cube::isVisited(){
    return visited;
}

void Cube::setVisited(const bool choice){
    this->visited = choice;
}
