
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Part 1: 3263
// Part 2: -

int getGameIndex(string line) {

    int found = line.find(":");
    string gameIndexStr = line.substr(5, found - 5);
    int gameIndex = atoi(gameIndexStr.c_str());

    return gameIndex;
}

string getGameResults(string line) {
    int colonIndex = line.find(":");

    return line.substr(colonIndex + 2);
}

string getNextGame(string gameResults) {

    unsigned int foundComma = gameResults.find(",");
    unsigned int foundSemiColon = gameResults.find(";");

    if (foundComma > gameResults.size() && foundSemiColon > gameResults.size()) {
        return gameResults;
    }
    if (foundComma < foundSemiColon) {
       return gameResults.substr(0, foundComma);
    } else {
        return gameResults.substr(0, foundSemiColon);
    }
}

string getRestGames(string gameResults) {
    unsigned int foundComma = gameResults.find(",");
    unsigned int foundSemiColon = gameResults.find(";");
    
    if (foundComma > gameResults.size()  && foundSemiColon > gameResults.size()) {
        return "";
    }
    if (foundComma < foundSemiColon) {
        return gameResults.substr(foundComma + 2);
    }
    else {
        return gameResults.substr(foundSemiColon + 2);
    }
}


bool checkGame(string game) {

    int const MAX_RED = 12;
    int const MAX_GREEN = 13;
    int const MAX_BLUE = 14;

    string const RED = "red";
    string const BLUE = "blue";
    string const GREEN = "green";

    int gameSize = game.size();
    unsigned int foundBlue = game.find(BLUE);
    unsigned int foundRed = game.find(RED);
    unsigned int foundGreen = game.find(GREEN);

    if (foundBlue < gameSize) {
        return atoi(game.substr(0, foundBlue - 1).c_str()) <= MAX_BLUE;
    } else if (foundRed < gameSize) {
        return atoi(game.substr(0, foundRed - 1).c_str()) <= MAX_RED;
    } else {
        return atoi(game.substr(0, foundGreen - 1).c_str()) <= MAX_GREEN;
    }
}

int getMinOfGame(int prevMin, unsigned int colorIndex, string game) {
    int gameMin = atoi(game.substr(0, colorIndex - 1).c_str());

    if (prevMin > gameMin) {
        return prevMin;
    }
    else {
        return gameMin;
    }
}

int getMinOfLine(string gameResults) {

    bool isLastGame = false;
    bool shouldRun = true;

    string restGame = getRestGames(gameResults);
    string game = getNextGame(gameResults);

    int blueMin = 0;
    int greenMin = 0;
    int redMin = 0;

    string const RED = "red";
    string const BLUE = "blue";
    string const GREEN = "green";

    while (shouldRun) {

        int gameSize = game.size();

        unsigned int foundBlue = game.find(BLUE);
        unsigned int foundRed = game.find(RED);
        unsigned int foundGreen = game.find(GREEN);

        if (foundBlue < gameSize) {
            blueMin = getMinOfGame(blueMin, foundBlue, game);
        } else if (foundRed < gameSize) {
            redMin = getMinOfGame(redMin, foundRed, game);
        } else {
            greenMin = getMinOfGame(greenMin, foundGreen, game);
        }
        if (!isLastGame) {
            game = getNextGame(restGame);
            restGame = getRestGames(restGame);
        } else {
            shouldRun = false;
        }

        if (restGame == "") {
            isLastGame = true;
        }
    }

    return blueMin * greenMin * redMin;
}

bool checkPossible(string gameResults) {

    bool isLastGame = false;
    bool isPossible = true;

    string restGame = getRestGames(gameResults);
    string game = getNextGame(gameResults);
    
    isPossible = checkGame(game);

    while (!isLastGame && isPossible) {

        game = getNextGame(restGame);
        restGame = getRestGames(restGame);

        isPossible = checkGame(game);

        if (restGame == "") {
            isLastGame = true;
        }
    }

    return isPossible;
}

int main() {
    string line;
    ifstream inputFile("input.txt");
    //ifstream inputFile("test.txt");
    //ifstream inputFile("test2.txt");

    int sumPossible = 0;
    int sumMinAmount = 0;

    if (inputFile.is_open()) {

        while (getline(inputFile, line)) {
            bool isPossible = true;
            
            //cout << line << endl;

            int gameIndex = getGameIndex(line);
            string gameResults = getGameResults(line);

            isPossible = checkPossible(gameResults);
            if (isPossible) {
                sumPossible += gameIndex;
            }

            sumMinAmount += getMinOfLine(gameResults);
        }

        cout << "sum possible ids: " << sumPossible << endl;
        cout << "sum mins: " << sumMinAmount << endl;

        inputFile.close();
    }
}
