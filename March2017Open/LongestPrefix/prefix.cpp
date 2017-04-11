/*
ID: kml111
PROG: prefix
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int longestPrefix(const string &sequence, const vector<string> &primitives) {
	int slen = (int)sequence.length();
	vector<bool> prefixLength(slen + 1, false);
	prefixLength[0] = true;
	for (int i = 0; i < slen; ++i) {
		if (prefixLength[i]) {
			for (int j = 0; j < (int)primitives.size(); ++j) {
				int primlen = (int)primitives[j].length();
				string substring = sequence.substr(i, primlen);
				if (substring == primitives[j]) {
					prefixLength[i + primlen] = true;
				}
			}
		}
	}

	int largest = 0;
	for (int k = 0; k <= slen; ++k) {
		if (prefixLength[k]) {
			largest = k;
		}
	}
	return largest;
}

int main() {
	ofstream fout("prefix.out");
	ifstream fin("prefix.in");
	vector<string> primitives;
	string p;
	fin >> p;
	while (p != ".") {
		primitives.push_back(p);
		fin >> p;
	}
	string sequence;
	while (!fin.eof()) {
		string line; 
		fin >> line; 
		sequence += line; 
	}

	fout << longestPrefix(sequence, primitives) << endl;
	return 0;
}