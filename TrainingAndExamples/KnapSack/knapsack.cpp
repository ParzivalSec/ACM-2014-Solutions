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
const int maxN = 25;

// Maximales Volumen des Rucksackes
const int maxV = 1000;

// Anzahl der Elemente im Rucksack
int n = 0;

// Volumen des Rucksackes
int V = 0;

// Volumen der Gegenstaende
int v[maxN];

// Werte der Gegenstaende
int w[maxN];

// Vector fuer alle Gegenstaende die im Rucksack waren
vector<int> knapsack;

// Array um Ergebnisse zu speichern (dynamisierungs array)
int result[maxN][maxV + 1];

int main(int argc, char** argv)	{

	// Werte einlesen
	cout << "\033[36mPlease enter the number of elements you want me to handle: \033[0m";
	cin >> n;
	cout << endl;
	cout << "\033[36mAnd how much weight can you carry in your knapsack? \033[0m";
	cin >> V;
	//maxV = v;
	cout << endl;
	cout << "\033[36mOkay lets start with the items. But before, do you even lift ? That weight is ridiculous!\033[0m" << endl;
	for(int i=0;i<n;i++)	{
		cout << "\033[36mItem [" << i + 1 << "] Please enter Value and Weight seperated by space (2 3): \033[0m";
		cin >> w[i] >> v[i];
		cout << endl;
	}

	// Dynamisierungsarray mit -1 oder was eben leer bedeutet initialisieren
	for(int j=0;j<n;j++)	{
		memset(result[j], -1, (maxV + 1)* sizeof(int));
	}

	// Wert ueber rekursive Funktion berechnen
	int r = solve(V, 0);

	cout << "\033[31mBest value = " << r << "\033[0m" << endl;

	// Durch Backtracking hol ich jz die Items welche zum maximalen Wert fuehren
	// aus der result matrix

	// Suchen des Volumens bei maximalem Wert
	// Max Val ist immer in der ersten Spalte aufgrund der rekursion
	int currVol = -1; // -1 da 0 auftreten kann
	for(int i=0; i <= maxV  && currVol == -1; i++)	{
		if(r == result[0][i])	{
			currVol = i;
		}
	}	

	// Jetzt checken ob das item in den Rucksack passt
	// Wenn ja entfernen wir ihn aus dem Rucksack und schauen
	// ob der Wert an der neuen Stelle korrekt ist
	for(int i=0; i< n - 1; i++)	{
		if(currVol - v[i] >= 0 && r - w[i] == result[i + 1][currVol - v[i]])	{
			// Item war im Rucksack
			knapsack.push_back(i);
			cout << "DEBUG: One item choosen to have been in the knapsack" << endl;
			
			r -= w[i];
			currVol -= v[i];
		}
		else {
			cout << "Item not in kanpsack" << endl;
		}

	}

	// Testen des letzten Elementes, da Index i + 1 des result arrays nicht mehr vorhanden ist
	// Ist also jetzt noch etwas im Rucksack, kann es nur das letzte Item sein
	if(r > 0) knapsack.push_back(n - 1);	

	cout << "\033[32mYour knapsack holds the following items : \033[0m" << endl;
	for(int item : knapsack)	{
		cout << "\033[32mItem number [ " << item + 1 << " ] with Value [ " << w[item] << " ] and Weight [ " << v[item] << " ]\033[0m" << endl;
	}
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
