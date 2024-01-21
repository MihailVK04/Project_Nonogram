#include <iostream>
#include <string>
#include "Game_Body.h"
using namespace std;

constexpr int MAX_SIZE = 60;

int main()
{
    cout << "Enter username:\n";
    string user;
    string fileName;
    string sample[MAX_SIZE];
    string matrix[MAX_SIZE];
    string info[MAX_SIZE];
    int size = 0;
    int lives = 3;
    int squares = 0;
    correctUsername(user);
    checkForUser(user, fileName, sample, matrix, info, size, lives, squares);
    startGame(squares, sample, matrix, info, user, fileName, lives, size);
}

