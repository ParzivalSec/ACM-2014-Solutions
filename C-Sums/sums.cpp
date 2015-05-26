// Author: Lukas Vogl <lukas@codebrewer.net>
// Task : Problem C Sums
// Runtime: O(sqrt(n))

#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

int isPowerOf2(unsigned long x) {  return !((x-1)&x);}

int main(int argc, char** argv)	{

	int tests = 0;
	cin >> tests;

	while(--tests)	{
	int n = 0;
	// Read in testcases from stdin
	cin >> n;
	
	// Solve small gaussian equotation for n
	// 1 + 2 + 3 + ... + n = (n - 1) * n / 2
	// OR
	// k + (k + 1) + ( k + 2) + ... + (k + d -1) = (2k + d -1)*d / 2
	// (2k + d -1)*d = 2N --> (2k + d -1)*d/2 = N (= SUM)
	
	// Change formula to k = (2n - (d*d) + d)/2*d

	if(isPowerOf2(n)) {
		cout << "IMPOSSIBLE" << endl;
	}
	else	{
		
	int N = 2 * n;
	
	for(int d = 2; d <= n/2; d++)	{
		long k = (N - (d*d) + d)/(2*d);
		if(k > 0 && ((2*k + d -1)*d == N))	{
			if(d < n)	{
				int k = (N - (d*d) + d)/(2 * d);
				for(int i=0; i<d - 1; i++) cout << k+i << " + ";
				cout << k+d-1 << " = " <<  n  << endl;
			}
			break;
		}
	}	
	}
}
}
