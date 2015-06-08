/**
AUTHOR: Lukas Vogl
Problem: Knapsack Problem
**/
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

int solve( int currentVolume, int i );

// Maximale Anzahl an Gegenstaenden
const int maxN = 30;

// Maximales Volumen des Rucksackes
const int maxV = 30;

// Anzahl der Elemente im Rucksack
int n = 0;

// Volumen des Rucksackes
int V = 0;

// Volumen der Gegenstaende
int v[maxN];

// Werte der Gegenstaende
int w[maxN];

// Array um Ergebnisse zu speichern (dynamisierungs array)
int result[maxN][maxV + 1];

int main(int argc, char** argv)	{

	// Werte einlesen
	cout << "Please enter the number of elements you want me to handle: ";
	cin >> n;
	cout << endl;
	cout << "And how much weight can you carry in your knapsack? ";
	cin >> V;
	cout << endl;
	cout << "Okay lets start with the items. But before, do you even lift ? That weight is ridiculous!" << endl;
	for(int i=0;i<n;i++)	{
		cout << "Item [" << i << "] Please enter Value and Weight seperated by space (2 3): ";
		cin >> w[i] >> v[i];
		cout << endl;
	}

	// Dynamisierungsarray mit -1 oder was eben leer bedeutet initialisieren
	for(int j=0;j<n;j++)	{
		memset(result[j], -1, (maxV + 1)* sizeof(int));
	}

	// Wert ueber rekursive Funktion berechnen
	int r = solve(V, 0);

	cout << "Best value = " << r << endl;

}

int solve(int currentV, int item)	{
	if(item < n)	{
		int without = 0;
		int with = 0;
		// Wenn schon einmal berechnet mit diesem Gegenstand und Volumen kann man sich die Operationen sparen
		if(result[item][currentV] != -1)
			return result[item][currentV];
		
		// Loesen ohne aktuellem Gegenstand
		without = solve(currentV, item + 1);

		// Loesen mit aktuellem Gegenstand wenn noch Platz da ist
		// Nicht aufs istgleich vergessen (hat vorher net funtkioniert)
		if(currentV - v[item] >=  0)	{
			with = w[item] + solve(currentV - v[item], item + 1);
		}
		result[item][currentV] = max(with, without);
		return result[item][currentV];
	}
	return 0;	
}
