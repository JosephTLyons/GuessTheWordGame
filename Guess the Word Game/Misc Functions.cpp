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

// Add 60 newlines to clear screen so next player can't see previously entered word
void clearScreen()
{
    int numberOfNewlines = 60;
    
    for (int i = 0; i < numberOfNewlines; i++)
    {
        cout << "\n";
    }
}

void displayArrayContents(const char array[])
{
    for (int i = 1; array[i] != 0; i++)
    {
        cout << array[i];
        
        // Add newline every 4 letters - mod by 8 due to spacing between letters
        if (i % 8 == 0)
            cout << '\n';
    }
}

void displayVectorContents(const vector <char> &vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        cout << vector[i];
    }
}

void drawLine()
{
    cout << "\n*************\n\n";
}

bool repeatGame()
{
    char repeatGameOrNot;
    
    cout << "Would you like to play again? Y/N: ";
    cin >> repeatGameOrNot;
    
    //ignore newline generated from last cin >> statement
    cin.ignore();
    
    if(toupper(repeatGameOrNot) == 'Y')
    {
        return true;
    }
    
    else
    {
        return false;
    }
}
