/*
 * antwe841
 * bensu844
 *
 * The cube class stores information about a boggle cube such as
 * the letters on the sides of a boggle cube, which face is up,
 * and if the cube has been visited by the search algorithm.
 */

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

    /*
     * Forces the top letter
     */
    void forceTopLetter(char letter);

    /*
     * Returns whether the cube has been visited
     */
    bool isVisited();

    /*
     * Sets whether the cube has been visited
     */
    void setVisited(const bool choice);

private:
    string letters;
    string topLetter;
    bool visited;

};
#endif // CUBE_H
