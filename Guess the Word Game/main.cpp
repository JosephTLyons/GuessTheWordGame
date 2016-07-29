#include <iostream>
#include <ctype.h> //for toupper functions
#include <vector>  //for using vectors

using namespace std;

void EnterWordToBeGuessed(vector <char> &WordToGuess);
void ClearScreen();
void InitializeUnderlinesAndBlankSpaces(const vector <char> &WordToGuess, vector <char> &CorrectLetters);
void GuessWord(const vector <char> &WordToGuess, vector <char> &CorrectLetters);
bool SeeIfLetterGuessedIsInWord(const char &Input, const vector <char> &WordToGuess, int &PositionOfFoundLetter);
void InsertCorrectLetterInCorrectLetterVector(const vector <char> &WordToGuess, const int &PositionOfFoundLetter, vector <char> &CorrectLetters);
void TemporaryIndicationOfIncorrectGuess(const int NumOfIncorrectGuesses);//to be rewritten to display hangman

int main()
{
    vector <char> WordToBeGuessed;
    vector <char> CorrectLettersAndBlankSpaces;
    
    EnterWordToBeGuessed(WordToBeGuessed);
    
    InitializeUnderlinesAndBlankSpaces(WordToBeGuessed, CorrectLettersAndBlankSpaces);
    
    /* ADD NEWLINES TO CLEAR SCREEN */
    
    ClearScreen();
    
    GuessWord(WordToBeGuessed, CorrectLettersAndBlankSpaces);
}

void EnterWordToBeGuessed(vector <char> &WordToGuess)
{
    char Input;
    
    cout << "Enter word to be guessed: ";
    
    cin.get(Input);
    
    while (Input != '\n')
    {
        WordToGuess.push_back(toupper(Input));
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

void InitializeUnderlinesAndBlankSpaces(const vector <char> &WordToGuess, vector <char> &CorrectLetters)
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

void GuessWord(const vector <char> &WordToGuess, vector <char> &CorrectLetters)
{
    char Input;
    int NumberOfIncorrectGuesses = 0;//hard coded for now
    int PositionOfFoundLetter = -1;  //initialized at -1 because it uses array style notation, which starts at 0
    
    do
    {
        /* DISPLAY CORRECT LETTERS */
        
        cout << "Word to Guess: ";
        
        for (int i = 0; i < CorrectLetters.size(); i++)
        {
            cout << CorrectLetters[i];
        }
        
        cout << "\n\nGuess one letter: ";
        
        cin >> Input;
        cin.ignore();// IGNORE NEWLINE AFTER CIN >>
        
        /* SEEIFLETTERGUESSEDISINWORD WILL RETURN A TRUE IF LETTER IS FOUND, ONLY INCREMENT COUNTER IF LETTER ISN'T FOUND */
        /* IT ALSO HAS A REFERENCE PARAMETER THAT RETURNS THE POSITION OF A LETTER FOUND, IF IT IS FOUND */
        
        if (!SeeIfLetterGuessedIsInWord(Input, WordToGuess, PositionOfFoundLetter))
        {
            NumberOfIncorrectGuesses++;
        }
        
        if (PositionOfFoundLetter > -1)
        {
            InsertCorrectLetterInCorrectLetterVector(WordToGuess, PositionOfFoundLetter, CorrectLetters);
        }
        
        /* DISPLAY CORRECT LETTERS */
        
        if (NumberOfIncorrectGuesses > 0)
        {
            TemporaryIndicationOfIncorrectGuess(NumberOfIncorrectGuesses);
        }
        
        cout << "\n";
    }
    while (NumberOfIncorrectGuesses <= 7);
    
}

bool SeeIfLetterGuessedIsInWord(const char &Input, const vector <char> &WordToGuess, int &PositionOfFoundLetter)
{
    for (int i = 0; i < WordToGuess.size(); i++ )
    {
        /* CHECKING TO SEE IF LETTER IS ANYWHERE IN WORDTOGUESS, BY ITERATING THROUGH IT */
        
        if (toupper(Input) == WordToGuess[i])
        {
            PositionOfFoundLetter = i;
            return true;
        }
    }
    
    return false;
}

void InsertCorrectLetterInCorrectLetterVector(const vector <char> &WordToGuess, const int &PositionOfFoundLetter, vector <char> &CorrectLetters)
{
    CorrectLetters[PositionOfFoundLetter * 2] = WordToGuess[PositionOfFoundLetter];
}

void TemporaryIndicationOfIncorrectGuess(const int NumOfIncorrectGuesses)
{
    cout << "Incorrect guesses: ";
    
    for (int i = 0; i <NumOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
}