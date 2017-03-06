#include "GuessWord.hpp"
#include "Misc Functions.hpp"
using namespace std;

/*
    Fix spacging in ouput
    Change Xs to hangman drawing
    Change double spacgin to single spacing?
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
