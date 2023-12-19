#include "Number.h"

void Number::setMinX(int x) {
	minX = x;
}

void Number::setMaxX(int x) {
	maxX = x;
}

void Number::setY(int newY) {
	y = newY;
}

void Number::setNumber(int num) {
	number = num;
}

void Number::setShouldSum(bool shSum) {
	shouldSum = shSum;
}

int Number::getMinX() {
	return minX;
}

int Number::getMaxX() {
	return maxX;
}

int Number::getY() {
	return y;
}

int Number::getNumber() {
	return number;
}

bool Number::getShouldSum() {
	return shouldSum;
}