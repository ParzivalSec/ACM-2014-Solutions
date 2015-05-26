// Author: Lukas Vogl <lukas@codebrewer.net>
// Task: H - Good Morning
// Language: C++11

#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

// Returns the row from the request digit
int whichRow(int x)	{
	if(x==0) {
		return 4;
	}
	else {
		return (x+2)/3;
	}
}

// Returns the col from the request digit
int whichCol(int x)	{
	if(x==0)	{
		return 2;
	}
	else {
		return (x+2)%3+1;
	}

}	

bool checkPattern(int t, int o)	{
	return (whichCol(t) <= whichCol(o) && whichRow(t) <= whichRow(o));
}

// Checks if the single digits from the entered number match the only down-right pattern
// Drops all number > 100 down to < 100 because they are the same
// Splits them up to front digit (10er stellen) and back digits (1er stellen)
// COmpares the row/col from front/back to equals pattern

int isValidResult(int z)	{
	if(z < 10 || z == 100 || z == 200) {
		return true;
	}
	else if(z > 100) {
		z-= 100;
	}

	// Get 10er Stelle
	int front = z/10;
	// Get 1er Stelle
	int back = z%10;

	return checkPattern(front, back);
}


int main(int argc, char** argv)	{

int tests = 0;

cin >> tests;

while(tests-->0)	{
	int n = 0;
	int res = 1;
	cin >> n;
	
	// Brute force over all possible 200 cases and check if could be valid
	// If valid check if range between new possible value and n is smaller than 
	// actual result and n
	for(int i=1;i<=200;i++)	{
		//if(isValidResult(i)) cout << "True" << endl;
		if(isValidResult(i) && (abs(i - n) < abs(res - n)))	{
			res = i;
		}
	}
	cout << res << endl;
}
}
