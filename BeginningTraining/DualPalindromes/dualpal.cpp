/*
ID: kml111
PROG: dualpal
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool isPalindrome(const string &s) {
	if ((int)s.length() == 1) {
		return true;
	}
	else {
		for (int a = 0; a < (int)s.length() / 2; ++a) {
			if (s[a] != s[(int)s.length() - a - 1]) { // not a palindrome
				return false;
			}
			else {
				if (a == ((int)s.length() / 2) - 1 && s[a] == s[(int)s.length() - a - 1]) { // yes, a palindrome																			// insert pair of integer and square into map psquares
					return true;
				}
			}
		}
	}
}

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

void dualPalindromes(const int n, const int s, vector<int> &dualPals) {
	int howManyPals = 0;
	int a = s + 1;
	while (howManyPals < n) { // come up with n ints that are palindromes in at least two bases
		int countPalBases = 0;
		for (int b = 2; b <= 10; ++b) { // from base 2 thru 10
			// change int a into string ret, which is a in base b
			string ret;
			intToStringBase(a, ret, b); 
			if (isPalindrome(ret) == true) { // if ret is a palindrome
				countPalBases += 1; // add to the number of bases a is a palindrome in
			}
		}
		if (countPalBases >= 2) { // if a is a palindrome in at least 2 bases
			dualPals.push_back(a); // add a to the vector dualPals
			howManyPals += 1;
		}
		a += 1; // increase a
	}
}

int main() {
	// read files
	ofstream fout("dualpal.out");
	ifstream fin("dualpal.in");
	int n, s;
	fin >> n >> s;
	vector<int> dualPals;
	dualPalindromes(n, s, dualPals);
	for (int i : dualPals) {
		fout << i << endl;
	}
	return 0;
}