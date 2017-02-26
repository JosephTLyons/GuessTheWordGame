//
//  GuessWord.cpp
//  Guess the Word Game
//
//  Created by Joseph Lyons on 2/26/17.
//  Copyright © 2017 Joseph Lyons. All rights reserved.
//

#include <iostream>

#include "GuessWord.hpp"
#include "Misc Functions.hpp"

void GuessWord::enterWordToBeGuessed()
{
    char input;
    
    cout << "Enter word to be guessed: ";
    cin.get(input);
    
    while (input != '\n')
    {
        wordToBeGuessed.push_back(toupper(input));
        cin.get(input);
    }
}

void GuessWord::initializeUnderlinesAndBlankSpaces()
{
    const char underLine = '_';
    const char space     = ' ';
    
    /* FILL UP CORRECTLETTERS WITH TWICE AS MANY ELEMENTS AS WORDTOGUESS, USING WORDTOGUESS.SIZE() */
    for (int i = 0; i < wordToBeGuessed.size(); i++)
    {
        /* SKIP UNDERSCORE IF THE SPOT IS A SPACEBAR BETWEEN WORDS, ONLY PUT UNDERLINE IF ITS NOT A SPACE CHARACTER */
        if (wordToBeGuessed[i] != ' ')
        {
            correctLettersAndBlankSpaces.push_back(underLine);
        }
        
        /* IF SPOT IS A SPACEBAR, ADD ANOTHER */
        else
            correctLettersAndBlankSpaces.push_back(space);
        
        correctLettersAndBlankSpaces.push_back(space);
    }
}

void GuessWord::startGame()
{
    char input;
    
    /* PLACED SPACE BEFORE A SO I COULD USE 1 INSTEAD OF 0 IN ARRAY NOTATION TO ACCESS THE FIRST LETTER */
    char letterPool[] = " A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
    bool wordIsSolved;
    
    resetGame();
    
    do
    {
        clearScreen();
        drawLine();
        positionOfFoundLetter.clear();
        
        cout << "Word to Guess: ";
        
        displayVectorContents(correctLettersAndBlankSpaces);
        
        cout << "\n\nLetter pool: \n\n";
        
        displayArrayContents(letterPool);
        
        /* DISPLAY Xs ASSOCIATED WITH INCORRECT GUESSES */
        if (numberOfIncorrectGuesses > 0)
        {
            temporaryIndicationOfIncorrectGuess();
        }
        
        cout << "\n\nGuess one letter: ";
        
        cin >> input;
        input = toupper(input);// CONVERT TO UPPPERCASE SO THERE'S NO CASE ISSUES
        cin.ignore();// IGNORE NEWLINE AFTER CIN >>
        
        removeGuessedLetterFromLetterPool(letterPool, input);
        
        /* SEEIFLETTERGUESSEDISINWORD WILL RETURN A TRUE IF LETTER IS FOUND, ONLY INCREMENT COUNTER IF LETTER ISN'T FOUND */
        
        /* IT ALSO HAS A REFERENCE PARAMETER (VECTOR) THAT RETURNS THE POSITION(S) OF A LETTER FOUND, IF ANY ARE FOUND */
        
        if (!seeIfLetterGuessedIsInWord(input))
        {
            numberOfIncorrectGuesses++;
        }
        
        if (positionOfFoundLetter.size() > 0)
        {
            insertCorrectLetterInCorrectLetterVector();
        }
        
        /* THIS FUNCTION USES THE UNDERSCORES TO CHECK TO SEE IF A WORD IS SOLVED */
        /* IF UNDERLINES STILL EXIST, THEN THE WORD ISN'T SOLVED, IF NO UNDERLINES EXIST, THE WORD IS SOLVED */
        wordIsSolved = checkForUnderlines();
        
        cout << "\n";
    }
    while ((numberOfIncorrectGuesses < 7) && (wordIsSolved == false));
    
    dispalyWinOrLoseStatus();
    
    cout << "\n\nWord to Guess Was: ";
    
    displayVectorContents(wordToBeGuessed);
    
    cout << "\n\n";
}

void GuessWord::temporaryIndicationOfIncorrectGuess() const
{
    cout << "\n\nIncorrect guesses: ";
    
    for (int i = 0; i < numberOfIncorrectGuesses; i++)
    {
        cout << "X ";
    }
}

void GuessWord::removeGuessedLetterFromLetterPool(char letterPool[], const char &input)
{
    for (int i = 0; letterPool[i] != 0; i++)
    {
        if (letterPool[i] == input)
        {
            letterPool[i] = '_';
        }
    }
}

bool GuessWord::seeIfLetterGuessedIsInWord(const char &input)
{
    for (int i = 0; i < wordToBeGuessed.size(); i++ )
    {
        /* CHECKING TO SEE IF LETTER IS ANYWHERE IN WORDTOGUESS, BY ITERATING THROUGH IT */
        if (input == wordToBeGuessed[i])
        {
            positionOfFoundLetter.push_back(i);
        }
    }
    
    if (positionOfFoundLetter.size() > 0)
        return true;
    
    else
        return false;
}

void GuessWord::insertCorrectLetterInCorrectLetterVector()
{
    for (int i = 0; i < positionOfFoundLetter.size(); i++)
    {
        correctLettersAndBlankSpaces[positionOfFoundLetter[i] * 2] =
        wordToBeGuessed[positionOfFoundLetter[i]];
    }
}

// If any underlines are present, word isn't solved
// Return true if word is solved, else return false for word isn't solved
bool GuessWord::checkForUnderlines()
{
    for (int i = 0; i < correctLettersAndBlankSpaces.size(); i++)
    {
        if (correctLettersAndBlankSpaces[i] == '_')
        {
            return false;
        }
    }
    
    return true;
}

void GuessWord::dispalyWinOrLoseStatus()
{
    if (numberOfIncorrectGuesses >= 7)
    {
        cout << "You lose!";
    }
    
    else
    {
        cout << "You Won!";
    }
}

void GuessWord::resetGame()
{
    numberOfIncorrectGuesses = 0;
    
    wordToBeGuessed.clear();
    correctLettersAndBlankSpaces.clear();
    positionOfFoundLetter.clear();
    
    enterWordToBeGuessed();
    initializeUnderlinesAndBlankSpaces();
}
