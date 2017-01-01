/*
ID: kml111
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#pragma warning(disable:4996)

using namespace std;

void palindromicSquares(const int b, vector<pair<string, string>> &psquares) {
	for (int n = 1; n <= 300; ++n) { // go through every integer in base 10 from 1 to 300
		// write down square of integer
		int sq = n * n;

		// convert the integer and its square to base b
		char storagen [33];
		itoa(n, storagen, b);
		char storagesq[33];
		itoa(sq, storagesq, b);

		// convert char array to string
		string bn(storagen);
		string bsq(storagesq);

		// check if the square of bn is a palindrome
		if ((int)bsq.length() == 1) {
			psquares.push_back(pair<string, string>(bn, bsq));
		}
		else {
			for (int a = 0; a < (int)bsq.length() / 2; ++a) {
				if (bsq[a] != bsq[(int)bsq.length() - a - 1]) { // not a palindrome
					break;
				}
				else {
					if (a == ((int)bsq.length() / 2) - 1 && bsq[a] == bsq[(int)bsq.length() - a - 1]) { // yes, a palindrome																			// insert pair of integer and square into map psquares
						psquares.push_back(pair<string, string>(bn, bsq));
					}
				}
			}
		}
	}
}

int main() {
	// read files
	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");
	int b;
	fin >> b;

	// call function palindromicSquares
	vector<pair<string, string>> psquares;
	palindromicSquares(b, psquares);

	//print contents of psquares
	for (pair<string, string> p : psquares) {
		fout << p.first << " " << p.second << endl;
	}
	return 0;
}
