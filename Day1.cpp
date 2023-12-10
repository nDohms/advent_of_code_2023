// Day1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getFirstNumber(string line) {

    string letteredNumbers [] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    int firstNumber = 0;

    int digitNumber = 0;
    int writeNumber = 0;

    int digitNumberIndex = line.size();
    int writeNumberIndex = line.size();

    for (int i = 0; i < line.size(); i++) {
        if (isdigit(line.at(i))) {
            digitNumberIndex = i;
            digitNumber = line.at(i) - 48;
            break;
        }
    }

    for (int i = 0; i < 9; i++) {
        size_t found = line.find(letteredNumbers[i]);
        if (found != string::npos && found < writeNumberIndex) {
            writeNumberIndex = found;
            writeNumber = i + 1;
        }
    }

    cout << "digitNumberIndex: " << digitNumberIndex << "; writeNumberIndex: " << writeNumberIndex << endl;

    if (digitNumberIndex < writeNumberIndex) {
        firstNumber = digitNumber;
    }
    else {
        firstNumber = writeNumber;
    }
    
    cout << "first number: " << firstNumber * 10 << endl;

    return firstNumber * 10;
}

int getSecondNumber(string line) {

    string letteredNumbers[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    int secondNumber = 0;

    int digitNumber = 0;
    int digitNumberIndex = -1;

    for (int i = line.size() - 1; i > -1 ; i--) {
        if (isdigit(line.at(i))) {
            digitNumber = line.at(i) - 48;
            digitNumberIndex = i;
            break;
        }
    }

    int writeNumber = 0;
    int writeNumberIndex = -1;

    for (int i = 0; i < 9; i++) {
        int found = line.rfind(letteredNumbers[i]);
        if (found > writeNumberIndex) {
            writeNumberIndex = found;
            writeNumber = i + 1;
        }
    }

    if (digitNumberIndex > writeNumberIndex) {
        secondNumber = digitNumber;
    }
    else {
        secondNumber = writeNumber;
    }

    cout << "second number: " << secondNumber << endl;

    return secondNumber;
}

int main()
{
    
    string line;
    ifstream inputFile ("input.txt");
    //ifstream inputFile("test.txt");
    //ifstream inputFile("test2.txt");


    if (inputFile.is_open()) {
        unsigned int sum = 0;
        while (getline(inputFile, line)) {
            cout << "line: " << line << endl;

            int firstNumber = getFirstNumber(line);
            int secondNumber = getSecondNumber(line);

            int lineNumber = firstNumber + secondNumber;
            sum = sum + lineNumber;
        }
        cout << "Sum total is: " << sum << endl;
        inputFile.close();
    }
}