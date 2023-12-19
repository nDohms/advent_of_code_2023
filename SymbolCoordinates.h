#pragma once

class SymbolCoordinates {

private:
    int x;
    int y;
    char symbol;

public:
    void setX(int newX);
    void setY(int newY);
    void setSymbol(char s);

    int getX();
    int getY();
    char getSymbol();
};