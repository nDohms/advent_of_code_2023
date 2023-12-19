#pragma once

class Number {
private:
	int minX = -1;
	int maxX = -1;
	int y = -1;
	int number = 0;

	bool shouldSum = false;

public:
	void setMinX(int x);
	void setMaxX(int x);
	void setY(int newY);
	void setNumber(int number);
	void setShouldSum(bool shSum);

	int getMinX();
	int getMaxX();
	int getY();
	int getNumber();
	bool getShouldSum();
};