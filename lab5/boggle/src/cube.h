#ifndef CUBE_H
#define CUBE_H

#include<string>

using namespace std;

class Cube
{
public:
    Cube(const string& letters);

    Cube(const char letter);

    /*
     * Sets topLetter to a random letter from the letters string
     */
    void shake();

    /*
     * Gets the top letter
     */
    char getTopLetter();

    bool isVisited();

    void setVisited(const bool choice);

private:
    string letters;
    char topLetter;
    bool visited;

};
#endif // CUBE_H
