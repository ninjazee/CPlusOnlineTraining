/*
ID: kml111
PROG: palsquare
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

void reverseVectorChangeToString(const vector<char> &start, string &end) {
	end.resize((int)start.size(), '0');
	for (int c = 0; c < (int)start.size(); ++c) { // for each char in the vector<char> start
		end[c] = start[(int)start.size() - c - 1]; // add to string putting the chars in the back in the front
	}
}

void intToStringBase(const int n, string &ret, const int b) {
	vector<char> storage; // create empty storage vector
	int i = n;
	while (i / b != 0) {
		char c = (i % b > 9 ? i % b - 10 + 'A' : i % b + '0'); // if n % b > 9 then make c the correct letter, else make it the correct number
		storage.push_back(c); // add the character to the storage
		i = i / b; // repeat with n / b in place of n
	} 
	char c = (i % b > 9 ? i % b - 10 + 'A' : i % b + '0'); // add the last digit
	storage.push_back(c); // push it in
	reverseVectorChangeToString(storage, ret); // reverse it and change to string
}

void palindromicSquares(const int b, vector<pair<string, string>> &psquares) {
	for (int n = 1; n <= 300; ++n) { // go through every integer in base 10 from 1 to 300
		// write down square of integer
		int sq = n * n;

		// create strings for the numbers and its squares in the base
		string bn;
		string bsq;

		// convert the integer and its square to base b
		intToStringBase(n, bn, b);
		intToStringBase(sq, bsq, b);

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
