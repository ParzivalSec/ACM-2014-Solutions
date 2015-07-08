/**
* Author: Lukas Vogl <luaks@codebrewer.net>
* Task: Problem D - Wheels
* Optimized version
**/

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int gcd(int x, int y)   {
    if(x < y) {
        return gcd(y, x);
    }
    if(y == 0)  {
        return x;
    }
    return gcd(y, x%y);
}

int square(int x)   {
    return x*x;
}

int main()  {

    int testcases;
    cin >> testcases;
    while(testcases--)  {
        int wheels;
        cin >> wheels;
        vector<int> xCoord(wheels), yCoord(wheels), rad(wheels);
        vector<int> wheelMoving(wheels, false);
        // Read in all wheels
        for(int i=0; i<wheels; i++)  {
            cin >> xCoord[i] >> yCoord[i] >> rad[i];
        }
        // Use a queue to check all moving wheels with the others
        // Idea qith queue cam from ACM Cert '14 solution for java
        // Is more effective than checking every wheel whith every other
        queue<int> Queue;
        Queue.push(0);
        wheelMoving[0] = 1;
        while(!Queue.empty())   {
            int actIndex = Queue.front();
            Queue.pop();
            for(int i=0; i<wheels; i++)  {
                // If a wheel is not moving and the wheels are touching - add their movement direction to the vector
                // And add now moving wheel to the queue for the next turn
                if(wheelMoving[i] == 0 && square(xCoord[i] - xCoord[actIndex]) + square(yCoord[i] - yCoord[actIndex]) == square(rad[i]+rad[actIndex]))    {
                    wheelMoving[i] = -wheelMoving[actIndex];
                    Queue.push(i);
                }
            }
        }
        // Now we know which wheel is moving and in which direction (1 and -1)
        // We calculate the turns for each wheel and print them
        // Truns are calculated via the gcd from the first wheels radius and the current wheels radius
        for(int i=0; i<wheels; i++)  {
            if(wheelMoving[i] == 0)  {
                cout << "not moving" << endl;
            }
            else    {
                int turns = gcd(rad[0], rad[i]);
                cout << rad[0]/turns;
                if(rad[i]>turns)
                    cout << "/" << rad[i]/turns;
                cout << (wheelMoving[i]==1 ? " clockwise" : " counterclockwise") << endl;
            
            }
        }
    }
}
