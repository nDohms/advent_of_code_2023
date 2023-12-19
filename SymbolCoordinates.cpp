#include "SymbolCoordinates.h"

void SymbolCoordinates::setX(int newX) {
    x = newX;
}

void SymbolCoordinates::setY(int newY) {
    y = newY;
}

void SymbolCoordinates::setSymbol(char s) {
    symbol = s;
}

int SymbolCoordinates::getX() {
    return x;
}

int SymbolCoordinates::getY() {
    return y;
}

char SymbolCoordinates::getSymbol() {
    return symbol;
}