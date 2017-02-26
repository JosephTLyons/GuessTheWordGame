#include <iostream>
#include <ctype.h> //for toupper functions
#include <vector>  //for using vectors
#include "Misc Functions.hpp"

using namespace std;

void enterWordToBeGuessed(vector<char> &WordToGuess);
void initializeUnderlinesAndBlankSpaces(const vector<char> &WordToGuess, vector<char> &CorrectLetters);
void guessWord(const vector<char> &WordToGuess, vector<char> &CorrectLetters);
void temporaryIndicationOfIncorrectGuess(const int NumOfIncorrectGuesses);//to be rewritten to display hangman
void removeGuessedLetterFromLetterPool(char LetterPool[], const char &Input);
bool seeIfLetterGuessedIsInWord(const char &Input, const vector<char> &WordToGuess, vector<int> &PositionOfFoundLetter);
void insertCorrectLetterInCorrectLetterVector(const vector<char> &WordToGuess, const vector<int> &PositionOfFoundLetter, vector<char> &CorrectLetters);
bool checkForUnderlines(const vector<char> &CorrectLetters);

/*
 
 FIX SPACING IN OUTPUT
 
 CHANGE Xs TO THE HANGMAN DRAWING
 
 CHANGE DOUBLE SPACING TO SINGLE SPACING?
 
*/

int main()
{
    char repeatGame;
    vector <char> wordToBeGuessed;
    vector <char> correctLettersAndBlankSpaces;
    
    do
    {
        enterWordToBeGuessed(wordToBeGuessed);
        initializeUnderlinesAndBlankSpaces(wordToBeGuessed, correctLettersAndBlankSpaces);
        guessWord(wordToBeGuessed, correctLettersAndBlankSpaces);
        
        cout << "Would you like to play again? Y/N: ";
        cin >> repeatGame;
        cin.ignore();//ignore newline generated from last cin >> statement
        
        wordToBeGuessed.clear();
        correctLettersAndBlankSpaces.clear();
        
        drawLine();
    }
    while (toupper(repeatGame) == 'Y');
}

void enterWordToBeGuessed(vector<char> &wordToGuess)
{
    char input;
    
    cout << "Enter word to be guessed: ";
    cin.get(input);
    
    while (input != '\n')
    {
        wordToGuess.push_back(toupper(input));
        cin.get(input);
    }
}

void initializeUnderlinesAndBlankSpaces(const vector<char> &wordToGuess, vector<char> &correctLetters)
{
    const char underLine = '_';
    const char space     = ' ';
    
    /* FILL UP CORRECTLETTERS WITH TWICE AS MANY ELEMENTS AS WORDTOGUESS, USING WORDTOGUESS.SIZE() */
    
    for (int i = 0; i < wordToGuess.size(); i++)
    {
        /* SKIP UNDERSCORE IF THE SPOT IS A SPACEBAR BETWEEN WORDS, ONLY PUT UNDERLINE IF ITS NOT A SPACE CHARACTER */
        
        if (wordToGuess[i] != ' ')
        {
            correctLetters.push_back(underLine);
        }
        
        /* IF SPOT IS A SPACEBAR, ADD ANOTHER */
        
        else
            correctLetters.push_back(space);
        
        correctLetters.push_back(space);
    }
}

void guessWord(const vector<char> &wordToGuess, vector<char> &correctLetters)
{
    char input;
    int numberOfIncorrectGuesses = 0;
    vector <int> positionsOfFoundLetter;// EACH ELEMENT HOLDS THE POSITION OF THE LETTER GUESSED, IN RELATIONSHIP TO THE WORD BEING GUESSED
    
    /* PLACED SPACE BEFORE A SO I COULD USE 1 INSTEAD OF 0 IN ARRAY NOTATION TO ACCESS THE FIRST LETTER */
    char letterPool[] = " A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
    bool wordIsSolved;
    
    do
    {
        clearScreen();
        drawLine();
        
        positionsOfFoundLetter.clear();
        
        cout << "Word to Guess: ";
        
        displayVectorContents(correctLetters);
        
        cout << "\n\nLetter pool: \n\n";
        
        displayArrayContents(letterPool);
        
        /* DISPLAY Xs ASSOCIATED WITH INCORRECT GUESSES */
        if (numberOfIncorrectGuesses > 0)
        {
            temporaryIndicationOfIncorrectGuess(numberOfIncorrectGuesses);
        }
        
        cout << "\n\nGuess one letter: ";
        
        cin >> input;
        input = toupper(input);// CONVERT TO UPPPERCASE SO THERE'S NO CASE ISSUES
        cin.ignore();// IGNORE NEWLINE AFTER CIN >>
        
        removeGuessedLetterFromLetterPool(letterPool, input);
        
        /* SEEIFLETTERGUESSEDISINWORD WILL RETURN A TRUE IF LETTER IS FOUND, ONLY INCREMENT COUNTER IF LETTER ISN'T FOUND */
        
        /* IT ALSO HAS A REFERENCE PARAMETER (VECTOR) THAT RETURNS THE POSITION(S) OF A LETTER FOUND, IF ANY ARE FOUND */
        
        if (!seeIfLetterGuessedIsInWord(input, wordToGuess, positionsOfFoundLetter))
        {
            numberOfIncorrectGuesses++;
        }
        
        if (positionsOfFoundLetter.size() > 0)
        {
            insertCorrectLetterInCorrectLetterVector(wordToGuess, positionsOfFoundLetter, correctLetters);
        }
        
        /* THIS FUNCTION USES THE UNDERSCORES TO CHECK TO SEE IF A WORD IS SOLVED */
        
        /* IF UNDERLINES STILL EXIST, THEN THE WORD ISN'T SOLVED, IF NO UNDERLINES EXIST, THE WORD IS SOLVED */
        
        wordIsSolved = checkForUnderlines(correctLetters);
        
        cout << "\n";
    }
    while ((numberOfIncorrectGuesses < 7) && (wordIsSolved == false));
    
    if (numberOfIncorrectGuesses >= 7)
    {
        cout << "You lose!";
    }
    
    else
    {
        /* DISPLAY CORRECT LETTERS AND UNDERLINES */
        
        cout << "You Won!";
    }
    
    cout << "\n\nWord to Guess: ";
    
    displayVectorContents(correctLetters);
    
    cout << "\n\n";
}

void temporaryIndicationOfIncorrectGuess(const int numOfIncorrectGuesses)
{
    cout << "\n\nIncorrect guesses: ";
    
    for (int i = 0; i < numOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
}

void removeGuessedLetterFromLetterPool(char letterPool[], const char &input)
{
    for (int i = 0; letterPool[i] != 0; i++)
    {
        if (letterPool[i] == input)
        {
            letterPool[i] = '_';
        }
    }
}

bool seeIfLetterGuessedIsInWord(const char &input, const vector<char> &wordToGuess, vector<int> &positionsOfFoundLetter)
{
    for (int i = 0; i < wordToGuess.size(); i++ )
    {
        /* CHECKING TO SEE IF LETTER IS ANYWHERE IN WORDTOGUESS, BY ITERATING THROUGH IT */
        
        if (input == wordToGuess[i])
        {
            positionsOfFoundLetter.push_back(i);
        }
    }
    
    if (positionsOfFoundLetter.size() > 0)
        return true;
    
    else
        return false;
}

void insertCorrectLetterInCorrectLetterVector(const vector<char> &wordToGuess, const vector<int> &positionOfFoundLetter, vector <char> &correctLetters)
{
    for (int i = 0; i < positionOfFoundLetter.size(); i++)
    {
        correctLetters[positionOfFoundLetter[i] * 2] = wordToGuess[positionOfFoundLetter[i]];
    }
}

bool checkForUnderlines(const vector<char> &correctLetters)
{
    /* RETURN TRUE IS WORD IS SOLVED, RETURN FALSE IF WORD ISN'T SOLVED */
    
    for (int i = 0; i < correctLetters.size(); i++)
    {
        if (correctLetters[i] == '_')
        {
            return false;
        }
    }
    
    return true;
}
