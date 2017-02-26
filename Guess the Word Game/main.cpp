#include "GuessWord.hpp"
#include "Misc Functions.hpp"
using namespace std;

/*
    FIX SPACING IN OUTPUT
    CHANGE Xs TO THE HANGMAN DRAWING
    CHANGE DOUBLE SPACING TO SINGLE SPACING?
    Guessing the same wrong letter twice shouldn't count as an incorrect guess
*/

int main()
{
    bool repeat;
    GuessWord gameInstance;
    
    do
    {
        gameInstance.startGame();
        repeat = repeatGame();
        drawLine();
    }
    while(repeat);
}
