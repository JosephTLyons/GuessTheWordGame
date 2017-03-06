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

    // Fill up correctLetters with twice as many elements as WordToGuess, using wordToGuess.size()
    for (int i = 0; i < wordToBeGuessed.size(); i++)
    {
        // Skip underscore if the spot is a spacebar between words
        // Only put underline if its not a space
        if (wordToBeGuessed[i] != ' ')
        {
            correctLettersAndBlankSpaces.push_back(underLine);
        }

        // If spot is a spacebar, add another
        else
            correctLettersAndBlankSpaces.push_back(space);

        correctLettersAndBlankSpaces.push_back(space);
    }
}

void GuessWord::startGame()
{
    char input;

    // Placed space before a so I could use 1 instead of 0
    // in array notation to access the first letter
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

        // Displays Xs associated with incorrect guesses
        if (numberOfIncorrectGuesses > 0)
        {
            temporaryIndicationOfIncorrectGuess();
        }

        cout << "\n\nGuess one letter: ";

        cin >> input;
        input = toupper(input);// Covert to uppercase so there's no case issues
        cin.ignore();// Ignore newline after cin >>

        removeGuessedLetterFromLetterPool(letterPool, input);

        // seeIfLetterGuessesInWord will return a true if letter is found
        // Only incremenet count4er if letter isn't found
        // It also has a reference paramater (vector) that returns the position(s)
        // Of a letter found, if any are found
        if (!seeIfLetterGuessedIsInWord(input))
        {
            numberOfIncorrectGuesses++;
        }

        if (positionOfFoundLetter.size() > 0)
        {
            insertCorrectLetterInCorrectLetterVector();
        }

        // This function uses the underscores to check to see if a word is solved
        // If underlines still exist, then the word isnt solved
        // If no underlines exists, then the word is solved
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
        // Checking to see if lettet is anywhere in WordToGuess, by iterating through it
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
