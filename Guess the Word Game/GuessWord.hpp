//
//  GuessWord.hpp
//  Guess the Word Game
//
//  Created by Joseph Lyons on 2/26/17.
//  Copyright © 2017 Joseph Lyons. All rights reserved.
//

#ifndef GuessWord_hpp
#define GuessWord_hpp

#include <vector>

using namespace std;

class GuessWord
{
private:
    
    vector<char> wordToBeGuessed;
    vector<char> correctLettersAndBlankSpaces;
    vector<int> positionOfFoundLetter;// EACH ELEMENT HOLDS THE POSITION OF THE LETTER GUESSED, IN RELATIONSHIP TO THE WORD BEING GUESSED
    
    int numberOfIncorrectGuesses;
    
    void enterWordToBeGuessed();
    void initializeUnderlinesAndBlankSpaces();
    void temporaryIndicationOfIncorrectGuess() const;
    void removeGuessedLetterFromLetterPool(char letterPool[], const char &input);
    bool seeIfLetterGuessedIsInWord(const char &input);
    void insertCorrectLetterInCorrectLetterVector();
    bool checkForUnderlines();
    void dispalyWinOrLoseStatus();
    void resetGame();

    
public:
    
    void startGame();
};

#endif /* GuessWord_hpp */
