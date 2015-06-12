/**
Author: Lukas Vogl
Problem: D - Wheels
**/

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

long gcd(unsigned long a,unsigned long b) 
{ 
    for(;;) 
    { 
        if(a==0) // trap if a==0 
            return b; 
        b%=a; // otherwise here would be an error 
        if(b==0) // trap if b==0 
            return a; 
        a%=b; // otherwise here would be an error 
    } 
}

class node {
public:
	int id;
	int x;
	int y;
	int r;
	vector<node*>connected_wheels;

	node(int i, int xi, int yi, int ri)	{
		this->id = i;
		this->x = xi;
		this->y = yi;
		this->r = ri;
	};

	~node(){};

	string computeTurns(int r1, int rx)	{
		ostringstream output;
		double x = r1/rx;
		if(r1 == rx)	{
			output << 1;
		}
		else if(r1 % rx == 0)	{
			int d = (int)r1 / rx;
			output << d;
		}		
		else	{
			// Use eulian ggt algo to determine ggt and devide bz it
			int a = gcd(r1, rx);
			if(a > 0)	{
				output << r1/a << "/" << rx/a;
				return output.str();
			}			
			output << r1 << "/" << rx;
		}
		return output.str();
	}
	
	void printMovement(int RadI, bool even)	{
		string movementStr = "";
		movementStr = computeTurns(RadI, this->r);

		if(even)	{
			cout << movementStr << " counterclockwise" << endl;
		}
		else	{
			cout << movementStr << " clockwise" << endl;
		}
	};

	void connect(node* w)	{ connected_wheels.push_back(w); };

	void printConnectedComponents(node* firstWheel, int distance)	{
		if(connected_wheels.size() == 0)	{
			cout << "not moving" << endl;
			return;
		}
		for(int i=0;i<connected_wheels.size();i++)	{
			if(connected_wheels[i]->id > this->id)	{
				// cout << "Print Wheel " << connected_wheels[i]->id << endl;
				connected_wheels[i]->printMovement(firstWheel->r, (distance+1)%2 == 0);
			}
		}
	}	
};

bool touch(node* one, node* two)	{
	int vec1 = two->x - one->x;
	int vec2 = two->y - one->y;

	if(sqrt((vec1 * vec1) + (vec2 * vec2)) == one->r + two->r) return true;
	return false;
}

vector<node*> wheels;

int main()	{
int tests = 0;

cin >> tests;

while(tests--)	{
	int wheelsNum = 0;
	cin >> wheelsNum;
	int id = 1;
	while(wheelsNum--)	{
		int x,y,r = 0;
		cin >> x >> y >> r;
		wheels.push_back(new node(id, x, y, r));
		id++;
	}
	for(int i=0;i<wheels.size();i++)	{
		for(int j=0;j<wheels.size();j++)	{
			if(touch(wheels[i], wheels[j]))	{
				//cout << "Wheels [" << i + 1 << "] and [" << j + 1 << "] touching" << endl;
				wheels[i]->connect(wheels[j]);
			}
		}
	}
	wheels[0]->printMovement(wheels[0]->r, 1%2 == 0);
	for(int i=0;i<wheels.size();i++)	{
		wheels[i]->printConnectedComponents(wheels[0], i+1);
	}
	wheels.clear();
}
}
