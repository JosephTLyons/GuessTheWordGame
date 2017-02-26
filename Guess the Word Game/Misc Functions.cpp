//
//  Misc Functions.cpp
//  Guess the Word Game
//
//  Created by Joseph Lyons on 2/25/17.
//  Copyright © 2017 Joseph Lyons. All rights reserved.
//

#include <iostream>
#include "Misc Functions.hpp"

using namespace std;

void drawLine()
{
    cout << "\n*************\n\n";
}

// ADD 60 NEWLINES TO CLEAR SCREEN SO NEXT PLAYER CAN'T SEE PREVIOUSLY ENTERED WORD
void clearScreen()
{
    int numberOfNewlines = 60;
    
    for (int i = 0; i < numberOfNewlines; i++)
    {
        cout << "\n";
    }
}

void displayVectorContents(const vector <char> &vect)
{
    for (int i = 0; i < vect.size(); i++)
    {
        cout << vect[i];
    }
}

void displayArrayContents(const char array[])
{
    for (int i = 1; array[i] != 0; i++)
    {
        cout << array[i];
        
        /* ADD NEWLINE EVERY 4 LETTERS - EVERY 8 BECAUSE OF SPACING BETWEEEN LETERS MAKES IT DOUBLE LENGTH */
        
        if (i % 8 == 0)
            cout << '\n';
    }
}

void repeatGame(char &repeatGameOrNot)
{
    cout << "Would you like to play again? Y/N: ";
    cin >> repeatGameOrNot;
    cin.ignore();//ignore newline generated from last cin >> statement
}
