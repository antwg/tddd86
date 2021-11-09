#ifndef CUBE_H
#define CUBE_H

#include<string>

using namespace std;

class Cube
{
public:
    Cube();

    Cube(const string& letters);

    /*
     * Sets topLetter to a random letter from the letters string
     */
    void shake();

    /*
     * Gets the top letter
     */
    string getTopLetter();

    void forceTopLetter(char letter);

    bool isVisited();

    void setVisited(const bool choice);

private:
    string letters;
    string topLetter;
    bool visited;

};
#endif // CUBE_H
