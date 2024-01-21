#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

bool checkFileNames(string user) {
    for (int j = 1; j < 4; j++) {
        string e = "E." + to_string(j);
        e = e + ".txt";
        string n = "N." + to_string(j);
        n = n + ".txt";
        string i = "I." + to_string(j);
        i = i + ".txt";
        string h = "H." + to_string(j);
        h = h + ".txt";
        string m = "M." + to_string(j);
        m = m + ".txt";
        if (user == e || user == n || user == i || user == h || user == m) {
            cout << "Invalid expression! Enter appropriate username!\n";
            return false;
        }
    }
    return true;
}

void correctUsername(string& user) {
    bool correct = false;
    while (!correct) {
        getline(cin, user);
        if (user + ".txt" == "LastUsers.txt") {
            cout << "Invalid expression! Enter appropriate username!\n";
            continue;
        }
        correct = checkFileNames(user + ".txt");
    }
}

void fillingSample(string level, string* table, string* info, int& size, int& squares) {
    fstream readLevel;
    readLevel.open(level, fstream::in | fstream::app);
    string buffer;
    int i = 0;
    int j = 0;
    bool seen = true;
    bool seenAgain = true;
    while (getline(readLevel, buffer)) {
        if (buffer != ":" && seen) {
            table[i] = buffer;
            i++;
            continue;
        }
        else if(seen){
            seen = false;
            continue;
        }
        if (buffer != ":" && seenAgain) {
            info[j] = buffer;
            j++;
            continue;
        }
        else if(seenAgain){
            seenAgain = false;
            continue;
        }
        squares = stoi(buffer);
    }
    readLevel.close();
    size = i;
}

bool questionForOldUser(string a) {
    bool correct = false;
    while (!correct) {
        if (a == "y") {
            correct = true;
            return false;
        }
        else if (a == "n") {
            correct = true;
            return true;
        }
        else {
            cout << "Wrong input! Try aggain!\n";
            cin >> a;
        }
    }
}

void emptyMatrix(string* matrix, int size) {
    string row;
    for (int i = 0; i < size; i++) {
        row = row + "_ ";
    }
    for (int i = 0; i < size; i++) {
        matrix[i] = row;
    }
}

string chosenLevel(string a, unsigned int digit) {
    string l;
    if (a == "E" || a == "N" || a == "I" || a == "H" || a == "M") {
        l = l + a;
    }
    if (digit >= 1 && digit <= 3) {
        l = l + '.' + to_string(digit) + ".txt";
    }
    return l;
}

void checkForDificulty(string& a, bool& correct) {
    if (a == "E" || a == "N" || a == "I" || a == "H" || a == "M") {
        correct = true;
    }
    else {
        cout << "Wrong input! Try again:\n";
        correct = false;
        cin >> a;
    }
}

void getSample(string a, string& fileName, string* sample, string* info, int& size, int& squares) {
    bool correct = false;
    while (!correct)
    {
        checkForDificulty(a, correct);
    }
    srand(time(0));
    unsigned int digit = 1 + rand() % 3;
    fileName = chosenLevel(a, digit);
    fillingSample(fileName, sample, info, size, squares);
}

void choosingDificulty(string& fileName, string* sample, string* matrix, string* info, int& size, int& squares) {
    cout << "Choose dificulty:\n";
    cout << "(E - Easy, N - Normal, I - Intermediate, H - Hard, M - Master)\n";
    string a;
    cin >> a;
    getSample(a, fileName, sample, info, size, squares);
    emptyMatrix(matrix, size);
}

void oldUser(string* sample, string* matrix, string* info,string& fileName, string name, int& size, int& lives, int& squares) {
    string playerLives, leftSquares, buffer;
    bool endIf = true;
    name = name + ".txt";
    fstream readPlayerProfile;
    readPlayerProfile.open(name, fstream::in | fstream::app);
    getline(readPlayerProfile, fileName);
    while (getline(readPlayerProfile, buffer)) {
        if (buffer != ":" && endIf) {
            matrix[size] = buffer;
            size++;
            continue;
        }
        else {
            endIf = false;
        }
        getline(readPlayerProfile, playerLives);
        getline(readPlayerProfile, leftSquares);
    }
    readPlayerProfile.close();
    lives = stoi(playerLives);
    squares = stoi(leftSquares);
    fillingSample(fileName, sample, info, size, squares);
}

void checkForUser(string user, string& fileName, string* sample, string* matrix, string* info, int& size, int& lives, int& squares) {
    bool condition = true;
    fstream read;
    read.open("LastUsers.txt", fstream::in | fstream::app);
    string buffer;
    while (getline(read, buffer)) {
        if (user == buffer) {
            cout << "Do you want to play your last saved game?(y/n)\n";
            string a;
            cin >> a;
            condition = questionForOldUser(a);
            bool breaking = condition;
            if (breaking) {
                break;
            }
            oldUser(sample, matrix, info, fileName, user, size, lives, squares);
        }
    }
    read.close();
    if (condition) {
        choosingDificulty(fileName, sample, matrix , info , size, squares);
    }
}
