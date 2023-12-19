
#include <iostream>
#include <fstream>
#include <string>
#include "SymbolCoordinates.h"
#include "Number.h"

using namespace std;

int getNumberOfSymbolsInLine(string line) {
    int counter = 0;

    for (int i = 0; i < line.size(); i++) {
        if (!isalnum(line.at(i)) && line.at(i) != '.') {
            counter++;
        }
    }

    return counter;
}

SymbolCoordinates getCoordinates(string line, int y, int startX) {
    SymbolCoordinates sc;
    sc.setY(y);
    for (int i = startX; i < line.size(); i++) {
        if (!isalnum(line.at(i)) && line.at(i) != '.') {
            sc.setX(i);
            sc.setSymbol(line.at(i));
            return sc;
        }
    }
}

bool shouldSum(SymbolCoordinates sc, Number num) {
    int numMinX = num.getMinX() == 0 ? num.getMinX() : num.getMinX() - 1;
    int numMinY = num.getY() == 0 ? num.getY() : num.getY() - 1;
    return (num.getY() + 1 >= sc.getY() 
        && numMinY <= sc.getY() 
        && sc.getX() <= num.getMaxX() + 1 
        && sc.getX()  >= numMinX);
}

int main()
{
    string line;
    
    ifstream inputFile("input.txt");
    //ifstream inputFile("input2.txt");
    //ifstream inputFile("test.txt");
    //ifstream inputFile("test2.txt");

    if (inputFile.is_open()) {
        int y = 0;
        
        int symbolIndex = 0;
        int symbolArrayLength = 30;
        SymbolCoordinates *symbolCoordinates;
        symbolCoordinates = new SymbolCoordinates[30];

        int numbersIndex = 0;
        int numberArrayLength = 30;
        Number* numbers;
        numbers = new Number[30];

        Number num;
        SymbolCoordinates sc;

        while (getline(inputFile, line)) {
            
            bool startDigit = true;
            string number = "";

            num.setY(y);
            sc.setY(y);

            for (int i = 0; i < line.size(); i++) {

                if (!isalnum(line.at(i)) && line.at(i) != '.') {
                    if (symbolIndex + 1 == symbolArrayLength) {
                        int newSymbolArrayLength = symbolArrayLength + 30;
                        SymbolCoordinates* scs = new SymbolCoordinates[newSymbolArrayLength];

                        for (int j = 0; j < symbolArrayLength; j++) {
                            scs[j] = symbolCoordinates[j];
                        }

                        delete[] symbolCoordinates;
                        symbolCoordinates = scs;
                        symbolArrayLength = newSymbolArrayLength;
                    }

                    sc.setX(i);
                    sc.setSymbol(line.at(i));

                    symbolCoordinates[symbolIndex] = sc;
                    symbolIndex++;
                }
                if (i == line.size() - 1 && isdigit(line.at(i))) {

                    if (numbersIndex + 1 == numberArrayLength) {
                        int newNumberArrayLength = numberArrayLength + 30;
                        Number* nums = new Number[newNumberArrayLength];

                        for (int j = 0; j < numberArrayLength; j++) {
                            nums[j] = numbers[j];
                        }

                        delete[] numbers;
                        numbers = nums;
                        numberArrayLength = newNumberArrayLength;
                    }
                    num.setMaxX(i);
                    num.setNumber(atoi(number.c_str()));

                    numbers[numbersIndex] = num;
                    numbersIndex++;
                    number = "";
                }
                else if (isdigit(line.at(i)) && startDigit) {
                    num.setMinX(i);
                    startDigit = false;
                    number += line.at(i);
                }
                else if (!isdigit(line.at(i)) && !startDigit) {
                    startDigit = true;

                    if (numbersIndex + 1 == numberArrayLength) {
                        int newNumberArrayLength = numberArrayLength + 30;
                        Number* nums = new Number[newNumberArrayLength];

                        for (int j = 0; j < numberArrayLength; j++) {
                            nums[j] = numbers[j];
                        }

                        delete[] numbers;
                        numbers = nums;
                        numberArrayLength = newNumberArrayLength;
                    }
                    num.setMaxX(i - 1);
                    num.setNumber(atoi(number.c_str()));

                    numbers[numbersIndex] = num;
                    numbersIndex++;
                    number = "";
                }
                else if(isdigit(line.at(i))) {
                    number += line.at(i);
                }
            }

            y++;
        }

        long sumNumbers = 0;

        for (int i = 0; i < symbolIndex; i++) {
            sc = symbolCoordinates[i];
            cout << sc.getSymbol() << endl;
            for (int j = 0; j < numbersIndex; j++) {
                num = numbers[j];
                if (shouldSum(sc, num)) {
                    sumNumbers += num.getNumber();
                    cout << num.getNumber() << endl;
                }
            }
        }

        std::cout << "Total: " << sumNumbers << endl;

        inputFile.close();
    }
}
