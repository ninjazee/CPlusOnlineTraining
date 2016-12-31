/*
ID: kml111
PROG: namenum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

long long translateNumber(string s) {
	long long num = 0;
	for (int c = 0; c < (int)s.length(); ++c) {
		char th = s[c];
		int val = (th >= 'Q' ? (th - 'Q') / 3 + 7 : (th - 'A') / 3 + 2);
		/*
		switch (s[c]) {
			case 'A': digits[c] = 2; break;
			case 'B': digits[c] = 2; break;
			case 'C': digits[c] = 2; break;
			case 'D': digits[c] = 3; break;
			case 'E': digits[c] = 3; break;
			case 'F': digits[c] = 3; break;
			case 'G': digits[c] = 4; break;
			case 'H': digits[c] = 4; break;
			case 'I': digits[c] = 4; break;
			case 'J': digits[c] = 5; break;
			case 'K': digits[c] = 5; break;
			case 'L': digits[c] = 5; break;
			case 'M': digits[c] = 6; break;
			case 'N': digits[c] = 6; break;
			case 'O': digits[c] = 6; break;
			case 'P': digits[c] = 7; break;
			case 'R': digits[c] = 7; break;
			case 'S': digits[c] = 7; break;
			case 'T': digits[c] = 8; break;
			case 'U': digits[c] = 8; break;
			case 'V': digits[c] = 8; break;
			case 'W': digits[c] = 9; break;
			case 'X': digits[c] = 9; break;
			case 'Y': digits[c] = 9; break;
		}
		*/
		num = num * 10 + val;
	}
	return num;
}

int main() {
	ofstream fout("namenum.out");
	ifstream fin("namenum.in");
	ifstream txt("dict.txt");
	long long n;
	fin >> n;
	multimap<long long, string> dict; 
	for (int i = 0; i < 4617; ++i) {
		string name;
		txt >> name;
		pair<long long, string> vname(translateNumber(name), name);
		dict.insert(vname);
	}
	
	auto ret = dict.equal_range(n);
	if (ret.first == ret.second) {
		fout << "NONE" << endl;
	}
	else {
		for (auto it = ret.first; it != ret.second; ++it) {
			fout << it->second << endl;
		}
	}
	return 0;
}