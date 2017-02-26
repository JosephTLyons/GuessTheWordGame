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
    GuessWord gameInstance;
    char repeatGameOrNot;
    
    do
    {
        gameInstance.enterWordToBeGuessed();
        gameInstance.initializeUnderlinesAndBlankSpaces();
        gameInstance.startGame();
        repeatGame(repeatGameOrNot);
        gameInstance.resetGame();
        drawLine();
    }
    while (toupper(repeatGameOrNot) == 'Y');
}
