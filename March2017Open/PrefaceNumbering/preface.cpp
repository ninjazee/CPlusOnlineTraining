/*
ID: kml111
PROG: preface
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string convert(const int x) { // convert number to roman numeral
	int num = x;
	string retnum;
	// test for 1000 (M)
	if (num >= 1000) { // larger than 1000
		for (int a = 0; a < num / 1000; ++a) { // add M digit to number
			retnum += 'M';
		}
	}
	num %= 1000; // get rid of 1000 since we already dealt with that
	
	// test for 100 (C, CD, D, CM)
	if (num >= 100) { // larger than 100
		if (num >= 900) { // hundreds digit: 900
			retnum += 'C';
			retnum += 'M';
		}
		else if (num >= 500) { // hundreds digit: 500-800
			retnum += 'D';
			for (int b = 0; b < (num - 500) / 100; ++b) {
				retnum += 'C';
			}
		}
		else if (num >= 400) { // hundreds digit: 400
			retnum += 'C';
			retnum += 'D';
		}
		else { // hundreds digit: 100-300
			for (int b = 0; b < num / 100; ++b) {
				retnum += 'C';
			}
		}
	}
	num %= 100; // get rid of 100 since we dealt with that

	// test for 10 (X, XL, L, XC)
	if (num >= 10) { // larger than 10
		if (num >= 90) { // tens digit: 90
			retnum += 'X';
			retnum += 'C';
		}
		else if (num >= 50) { // tens digit: 50-80
			retnum += 'L';
			for (int c = 0; c < (num - 50) / 10; ++c) {
				retnum += 'X';
			}
		}
		else if (num >= 40) { // tens digit: 40
			retnum += 'X';
			retnum += 'L';
		}
		else { // tens digit: 10-30
			for (int c = 0; c < num / 10; ++c) {
				retnum += 'X';
			}
		}
	}
	num %= 10; // get rid of 10 since we dealt with that

	// test for 1 (I, IV, V, IX)
	if (num >= 9) { // ones digit: 9
		retnum += 'I';
		retnum += 'X';
	}
	else if (num >= 5) { // ones digit: 5-8
		retnum += 'V';
		for (int c = 0; c < (num - 5); ++c) {
			retnum += 'I';
		}
	}
	else if (num >= 4) { // ones digit: 4
		retnum += 'I';
		retnum += 'V';
	}
	else { // ones digit: 1-3
		for (int c = 0; c < num; ++c) {
			retnum += 'I';
		}
	}

	return retnum;
}

int main() {
	ofstream fout("preface.out");
	ifstream fin("preface.in");
	int n;
	fin >> n;
	vector<int> romanNums(128, 0);

	for (int i = 1; i <= n; ++i) { // for each page
		string s = convert(i); // convert number to roman numeral
		for (int j = 0; j < (int)s.length(); ++j) { // for each character
			romanNums[s[j]] += 1; // add to the character tally
		}
	}
	
	if (romanNums['I'] != 0) {
		fout << 'I' << ' ' << romanNums['I'] << endl;
	}
	if (romanNums['V'] != 0) {
		fout << 'V' << ' ' << romanNums['V'] << endl;
	}
	if (romanNums['X'] != 0) {
		fout << 'X' << ' ' << romanNums['X'] << endl;
	}
	if (romanNums['L'] != 0) {
		fout << 'L' << ' ' << romanNums['L'] << endl;
	}
	if (romanNums['C'] != 0) {
		fout << 'C' << ' ' << romanNums['C'] << endl;
	}
	if (romanNums['D'] != 0) {
		fout << 'D' << ' ' << romanNums['D'] << endl;
	}
	if (romanNums['M'] != 0) {
		fout << 'M' << ' ' << romanNums['M'] << endl;
	}

	/*
	for (int k = 0; k < (int)romanNums.size(); ++k) {
		if (romanNums[k] != 0) {
			char numeral = k;
			fout << numeral << ' ' << romanNums[k] << endl;
		}
	}
	*/

	return 0;
}