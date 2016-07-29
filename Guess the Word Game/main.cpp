#include <iostream>
#include <ctype.h> //for toupper functions
#include <vector>  //for using vectors

using namespace std;

void EnterWordToBeGuessed(vector <char> &WordToGuess);
void ClearScreen();
void InitializeUnderlinesAndBlankSpaces(const vector <char> &WordToGuess, vector <char> &CorrectLetters);
void GuessWord(const vector <char> &WordToGuess, vector <char> &CorrectLetters);
void RemoveGuessedLetterFromLetterPool(char LetterPool[], const char &Input);
bool SeeIfLetterGuessedIsInWord(const char &Input, const vector <char> &WordToGuess, vector <int> &PositionOfFoundLetter);
void InsertCorrectLetterInCorrectLetterVector(const vector <char> &WordToGuess, const vector <int> &PositionOfFoundLetter, vector <char> &CorrectLetters);
void TemporaryIndicationOfIncorrectGuess(const int NumOfIncorrectGuesses);//to be rewritten to display hangman

/*
 
 DISPLAY FULL ALPHABET AND REMOVE THEM AS THE ARE USE
 DISPLAY ALL LETTERS USED
 
 CODE GAME TO END IF GUESSED ALL LETTERS - WIN
 CODE GAM TO END IF TOO MANY XS COME UP - END
 
 FIX SPACING IN OUTPUT
 
*/

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
    int NumberOfIncorrectGuesses = 0;
    vector <int> PositionOfFoundLetter;// EACH ELEMENT HOLDS THE POSITION OF THE LETTER GUESSED, IN RELATIONSHIP TO THE WORD BEING GUESSED
    
    /* PLACED SPACE BEFORE A SO I COULD USE 1 INSTEAD OF 0 IN ARRAY NOTATION TO ACCESS THE FIRST LETTER */
    char LetterPool[] = " A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
    
    do
    {
        PositionOfFoundLetter.clear();
        
        /* DISPLAY CORRECT LETTERS */
        
        cout << "Word to Guess: ";
        
        for (int i = 0; i < CorrectLetters.size(); i++)
        {
            cout << CorrectLetters[i];
        }
        
        /* DISPLAY LETTER POOL TO GUESS FROM */
        
        cout << "\n\nLetter pool: \n\n";
        
        for (int i = 1; LetterPool[i] != 0; i++)
        {
            cout << LetterPool[i];
            
            /* ADD NEWLINE EVERY 4 LETTERS */
            
            if (i % 8 == 0)
                cout << '\n';
        }
        
        cout << "\n\nGuess one letter: ";
        
        cin >> Input;
        Input = toupper(Input);// CONVERT TO UPPPERCASE SO THERE'S NO CASE ISSUES
        cin.ignore();// IGNORE NEWLINE AFTER CIN >>
        
        RemoveGuessedLetterFromLetterPool(LetterPool, Input);
        
        /* SEEIFLETTERGUESSEDISINWORD WILL RETURN A TRUE IF LETTER IS FOUND, ONLY INCREMENT COUNTER IF LETTER ISN'T FOUND */
        /* IT ALSO HAS A REFERENCE PARAMETER THAT RETURNS THE POSITION OF A LETTER FOUND, IF IT IS FOUND */
        
        if (!SeeIfLetterGuessedIsInWord(Input, WordToGuess, PositionOfFoundLetter))
        {
            NumberOfIncorrectGuesses++;
        }
        
        if (PositionOfFoundLetter.size() > 0)
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

void RemoveGuessedLetterFromLetterPool(char LetterPool[], const char &Input)
{
    for (int i = 0; LetterPool[i] != 0; i++)
    {
        if (LetterPool[i] == Input)
        {
            LetterPool[i] = '_';
        }
    }
}

bool SeeIfLetterGuessedIsInWord(const char &Input, const vector <char> &WordToGuess, vector <int> &PositionOfFoundLetter)
{
    for (int i = 0; i < WordToGuess.size(); i++ )
    {
        bool LetterFoundFlag;
        /* CHECKING TO SEE IF LETTER IS ANYWHERE IN WORDTOGUESS, BY ITERATING THROUGH IT */
        
        if (Input == WordToGuess[i])
        {
            PositionOfFoundLetter.push_back(i);
            LetterFoundFlag = true;
        }
    }
    
    if (PositionOfFoundLetter.size() > 0)
        return true;
    
    else
        return false;
}

void InsertCorrectLetterInCorrectLetterVector(const vector <char> &WordToGuess, const vector <int> &PositionOfFoundLetter, vector <char> &CorrectLetters)
{
    for (int i = 0; i < PositionOfFoundLetter.size(); i++)
    {
        CorrectLetters[PositionOfFoundLetter[i] * 2] = WordToGuess[PositionOfFoundLetter[i]];
    }
}

void TemporaryIndicationOfIncorrectGuess(const int NumOfIncorrectGuesses)
{
    cout << "Incorrect guesses: ";
    
    for (int i = 0; i <NumOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
}