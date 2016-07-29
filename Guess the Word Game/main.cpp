#include <iostream>
#include <vector>

using namespace std;

void EnterWordToBeGuessed(vector <char> &WordToGuess);
void ClearScreen();
void InitializeUnderlinesAndBlankSpaces(vector <char> &WordToGuess, vector <char> &CorrectLettersAndBlankSpaces);
void GuessWord(vector <char> &WordToGuess, vector <char> &CorrectLetters);
void TemporaryIndicationOfIncorrectGuess(int NumOfIncorrectGuesses);//to be rewritten to display hangman

int main()
{
    int NumberOfIncorrectGuesses = 6;
    vector <char> WordToBeGuessed;
    vector <char> CorrectLettersAndBlankSpaces;
    
    EnterWordToBeGuessed(WordToBeGuessed);
    
    InitializeUnderlinesAndBlankSpaces(WordToBeGuessed, CorrectLettersAndBlankSpaces);
    
    /* ADD NEWLINES TO CLEAR SCREEN */
    
    ClearScreen();
    
    GuessWord(WordToBeGuessed, CorrectLettersAndBlankSpaces);
    
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

void InitializeUnderlinesAndBlankSpaces(vector <char> &WordToGuess, vector <char> &CorrectLetters)
{
    char UnderLine = '_';
    char Space     = ' ';
    
    /* FILL UP CORRECTLETTERS WITH TWICE AS MANY ELEMENTS AS WORDTOGUESS, USING WORDTOGUESS.SIZE() */
    
    for (int i = 0; i < WordToGuess.size(); i++)
    {
        CorrectLetters.push_back(UnderLine);
        CorrectLetters.push_back(Space);
    }
}

void GuessWord(vector <char> &WordToGuess, vector <char> &CorrectLetters)
{
    char Input;
    
    /* DISPLAY CORRECT LETTERS */
    
    cout << "Word to Guess: ";
    
    for (int i = 0; i < CorrectLetters.size(); i++)
    {
        cout << CorrectLetters[i];
    }
    
    cout << "\n\nGuess one letter: ";
    
    cin >> Input;
    cin.ignore();// IGNORE NEWLINE AFTER CIN >>
    
    
}

void TemporaryIndicationOfIncorrectGuess(int NumOfIncorrectGuesses)
{
    cout << "Incorrect guesses: ";
    
    for (int i = 0; i <NumOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
}