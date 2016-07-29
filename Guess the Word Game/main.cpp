#include <iostream>
#include <vector>

using namespace std;

void EnterWordToBeGuessed(vector <char> &WordToGuess);
void ClearScreen();
void GuessWord(vector <char> &WordToGuess);
void DisplayCorrectLettersAndBlankSpaces(vector <char> &WordToGuess);
void TemporaryIndicationOfIncorrectGuess(int NumOfIncorrectGuesses);//to be rewritten to display hangman

int main()
{
    int NumberOfIncorrectGuesses = 6;
    vector <char> WordToBeGuessed;
    
    EnterWordToBeGuessed(WordToBeGuessed);
    
    /* ADD NEWLINES TO CLEAR SCREEN */
    
    ClearScreen();
    
    GuessWord(WordToBeGuessed);
    
    TemporaryIndicationOfIncorrectGuess(NumberOfIncorrectGuesses);
}

void EnterWordToBeGuessed(vector <char> &WordToGuess)
{
    char Input;
    
    cout << "Enter word to be guessed: ";
    
    cin.get(Input);
    
    while (Input != '\n')
    {
        WordToGuess.push_back(Input);
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

void GuessWord(vector <char> &WordToGuess)
{
    char Input;
    
    DisplayCorrectLettersAndBlankSpaces(WordToGuess);
    
    cout << "Guess one letter: ";
    
    cin >> Input;
    cin.ignore();// IGNORE NEWLINE AFTER CIN >>
    
    
}

void DisplayCorrectLettersAndBlankSpaces(vector <char> &WordToGuess)
{
    /* INITIALIZE VECTOR TO BE TWICE THE SIZE OF WORD TO GUESS, FOR BLANK SPACES BETWEEN */
    
    vector <char> CorrectLettersAndBlankSpaces(WordToGuess.size() * 2);
    
    
}

void TemporaryIndicationOfIncorrectGuess(int NumOfIncorrectGuesses)
{
    cout << "Incorrect guesses: ";
    
    for (int i = 0; i <NumOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
}