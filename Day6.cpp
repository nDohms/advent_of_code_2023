
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string trim(string line) {

    return line.substr(line.find_first_not_of(' '));
}

int main()
{

    string line;
    ifstream inputFile("input.txt");
    //ifstream inputFile("test.txt");

    if (inputFile.is_open()) {
        string lines[2];

        string lineTypes[] = { "Time:", "Distance:" };

        int numEntries = 1;

        int i = 0;

        while (getline(inputFile, line)) {

            cout << "line: " << line << endl;

            string handledLine = line.substr(lineTypes[i].length());
            handledLine = trim(handledLine);

            lines[i] = handledLine;
            i++;
        }

        inputFile.close();

        bool isPartNumber = false;

        unsigned long long int time = 0;
        unsigned long long int distance = 0;

        for (int i = 0; i < 2; i++) {
            string number = "";
            for (int ci = 0; ci < lines[i].length(); ci++) {
                char currentChar = lines[i].at(ci);
                if (isdigit(currentChar)) {
                    number += currentChar;
                }
            }       

            
            if (i == 0) {
                time = atol(number.c_str());
            }
            else {
                cout << "distance: " << number << endl;
                distance = strtoll(number.c_str(), NULL, 10);
            }
        }

        cout << "time: " << time << endl;
        cout << "distance: " << distance << endl;

        unsigned long long int wins = 0;
        for (unsigned long long distancePerMil = 1; distancePerMil < time; distancePerMil++) {
            unsigned long long restTime = time - distancePerMil;
            unsigned long long int achievedDistance = restTime * distancePerMil;
            
            if (achievedDistance > distance) {
                
                wins = time - (distancePerMil -1) * 2 - 1;
                break;
            }
        }

        cout << wins << endl;
    }
}

