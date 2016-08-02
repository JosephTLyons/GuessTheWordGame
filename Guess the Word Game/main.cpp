#include <iostream>
#include <ctype.h> //for toupper functions
#include <vector>  //for using vectors

using namespace std;

void EnterWordToBeGuessed(vector <char> &WordToGuess);
void InitializeUnderlinesAndBlankSpaces(const vector <char> &WordToGuess, vector <char> &CorrectLetters);
void GuessWord(const vector <char> &WordToGuess, vector <char> &CorrectLetters);
void DrawLine();
void ClearScreen();
void DisplayVectorContents(const vector <char> &CorrectLetters);
void DisplayArrayContents(const char Array[]);
void TemporaryIndicationOfIncorrectGuess(const int NumOfIncorrectGuesses);//to be rewritten to display hangman
void RemoveGuessedLetterFromLetterPool(char LetterPool[], const char &Input);
bool SeeIfLetterGuessedIsInWord(const char &Input, const vector <char> &WordToGuess, vector <int> &PositionOfFoundLetter);
void InsertCorrectLetterInCorrectLetterVector(const vector <char> &WordToGuess, const vector <int> &PositionOfFoundLetter, vector <char> &CorrectLetters);
bool CheckForUnderlines(const vector <char> &CorrectLetters);

/*
 
 FIX SPACING IN OUTPUT
 
 ADD ABILITY TO ADD SPACES (TWO WORDS OR MORE)
 
 DISPLAY FULL WORD WHEN DONE
 
 CHANGE Xs TO THE HANGMAN DRAWING
 
*/

int main()
{
    char RepeatGame;
    vector <char> WordToBeGuessed;
    vector <char> CorrectLettersAndBlankSpaces;
    
    do
    {
        EnterWordToBeGuessed(WordToBeGuessed);
        
        InitializeUnderlinesAndBlankSpaces(WordToBeGuessed, CorrectLettersAndBlankSpaces);
        
        GuessWord(WordToBeGuessed, CorrectLettersAndBlankSpaces);
        
        cout << "Would you like to play again? Y/N: ";
        cin >> RepeatGame;
        
        cin.ignore();//ignore newline generated from last CIN >> statement
        
        DrawLine();
    }
    while (toupper(RepeatGame) == 'Y');
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

void InitializeUnderlinesAndBlankSpaces(const vector <char> &WordToGuess, vector <char> &CorrectLetters)
{
    const char UnderLine = '_';
    const char Space     = ' ';
    
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
    vector <int> PositionsOfFoundLetter;// EACH ELEMENT HOLDS THE POSITION OF THE LETTER GUESSED, IN RELATIONSHIP TO THE WORD BEING GUESSED
    
    /* PLACED SPACE BEFORE A SO I COULD USE 1 INSTEAD OF 0 IN ARRAY NOTATION TO ACCESS THE FIRST LETTER */
    char LetterPool[] = " A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
    bool WordIsSolved;
    
    do
    {
        /* ADD NEWLINES TO CLEAR SCREEN */
        
        ClearScreen();
        
        /* DRAW SEPARATING LINE */
        
        DrawLine();
        
        /* CLEAR VECTOR OUT */
        
        PositionsOfFoundLetter.clear();
        
        /* DISPLAY CORRECT LETTERS */
        
        cout << "Word to Guess: ";
        
        DisplayVectorContents(CorrectLetters);
        
        /* DISPLAY LETTER POOL TO GUESS FROM */
        
        cout << "\n\nLetter pool: \n\n";
        
        DisplayArrayContents(LetterPool);
        
        /* DISPLAY Xs ASSOCIATED WITH INCORRECT GUESSES */
        
        if (NumberOfIncorrectGuesses > 0)
        {
            TemporaryIndicationOfIncorrectGuess(NumberOfIncorrectGuesses);
        }
        
        cout << "\n\nGuess one letter: ";
        
        cin >> Input;
        Input = toupper(Input);// CONVERT TO UPPPERCASE SO THERE'S NO CASE ISSUES
        cin.ignore();// IGNORE NEWLINE AFTER CIN >>
        
        RemoveGuessedLetterFromLetterPool(LetterPool, Input);
        
        /* SEEIFLETTERGUESSEDISINWORD WILL RETURN A TRUE IF LETTER IS FOUND, ONLY INCREMENT COUNTER IF LETTER ISN'T FOUND */
        /* IT ALSO HAS A REFERENCE PARAMETER (VECTOR) THAT RETURNS THE POSITION(S) OF A LETTER FOUND, IF ANY ARE FOUND */
        
        if (!SeeIfLetterGuessedIsInWord(Input, WordToGuess, PositionsOfFoundLetter))
        {
            NumberOfIncorrectGuesses++;
        }
        
        if (PositionsOfFoundLetter.size() > 0)
        {
            InsertCorrectLetterInCorrectLetterVector(WordToGuess, PositionsOfFoundLetter, CorrectLetters);
        }
        
        /* THIS FUNCTION USES THE UNDERSCORES TO CHECK TO SEE IF A WORD IS SOLVED */
        /* IF UNDERLINES STILL EXIST, THEN THE WORD ISN'T SOLVED, IF NO UNDERLINES EXIST, THE WORD IS SOLVED */
        
        WordIsSolved = CheckForUnderlines(CorrectLetters);
        
        cout << "\n";
    }
    while ((NumberOfIncorrectGuesses < 7) && (WordIsSolved == false));
    
    if (NumberOfIncorrectGuesses >= 7)
        cout << "You lose";
    
    else
        cout << "You guessed the word!";
    
    cout << "\n\n";
}

void DrawLine()
{
    cout << "\n*************\n\n";
}

void ClearScreen()
{
    /* ADD 60 NEWLINES TO CLEAR SCREEN SO NEXT PLAYER CAN'T SEE PREVIOUSLY ENTERED WORD */
    /* NUMBER CAN BE CHANGED AT ANY TIME, SIMPLY ADJUST i CONDITION */
    
    for (int i = 0; i < 60; i++)
    {
        cout << "\n";
    }
}

void DisplayVectorContents(const vector <char> &Vect)
{
    for (int i = 0; i < Vect.size(); i++)
    {
        cout << Vect[i];
    }
}

void DisplayArrayContents(const char Array[])
{
    for (int i = 1; Array[i] != 0; i++)
    {
        cout << Array[i];
        
        /* ADD NEWLINE EVERY 4 LETTERS */
        
        if (i % 8 == 0)
            cout << '\n';
    }
}

void TemporaryIndicationOfIncorrectGuess(const int NumOfIncorrectGuesses)
{
    cout << "\n\nIncorrect guesses: ";
    
    for (int i = 0; i < NumOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
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

bool SeeIfLetterGuessedIsInWord(const char &Input, const vector <char> &WordToGuess, vector <int> &PositionsOfFoundLetter)
{
    for (int i = 0; i < WordToGuess.size(); i++ )
    {
        bool LetterFoundFlag;
        /* CHECKING TO SEE IF LETTER IS ANYWHERE IN WORDTOGUESS, BY ITERATING THROUGH IT */
        
        if (Input == WordToGuess[i])
        {
            PositionsOfFoundLetter.push_back(i);
            LetterFoundFlag = true;
        }
    }
    
    if (PositionsOfFoundLetter.size() > 0)
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

bool CheckForUnderlines(const vector <char> &CorrectLetters)
{
    /* RETURN TRUE IS WORD IS SOLVED, RETURN FALSE IF WORD ISN'T SOLVED */
    
    for (int i = 0; i < CorrectLetters.size(); i++)
    {
        if (CorrectLetters[i] == '_')
        {
            return false;
        }
    }
    return true;
}