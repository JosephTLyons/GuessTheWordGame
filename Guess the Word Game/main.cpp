#include <iostream>
#include <vector>

using namespace std;

void EnterWord(vector <char> &WordToBeGuessed);
void ClearScreen();
void TemporaryIndicationOfIncorrectGuess(int NumOfIncorrectGuesses);

int main()
{
    int NumberOfIncorrectGuesses = 6;
    vector <char> WordToBeGuessed;
    
    EnterWord(WordToBeGuessed);
    
    /* ADD NEWLINES */
    
    ClearScreen();
    
    TemporaryIndicationOfIncorrectGuess(NumberOfIncorrectGuesses);
}

void EnterWord(vector <char> &WordToBeGuessed)
{
    char Input;
    
    cout << "Enter word to be guessed: ";
    
    cin.get(Input);
    
    while (Input != '\n')
    {
        WordToBeGuessed.push_back(Input);
        cin.get(Input);
    }
}

void ClearScreen()
{
    /* ADD 30 NEWLINES TO CLEAR SCREEN SO NEXT PLAYER CAN'T SEE PREVIOUSLY ENTERED WORD */
    /* NUMBER CAN BE CHANGED AT ANY TIME, SIMPLY ADJUST i CONDITION */
    
    for (int i = 0; i < 30; i++)
    {
        cout << "\n";
    }
}

void TemporaryIndicationOfIncorrectGuess(int NumOfIncorrectGuesses)
{
    cout << "Incorrect guesses: ";
    
    for (int i = 0; i <NumOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
}