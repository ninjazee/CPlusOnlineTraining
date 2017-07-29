/*
ID: kml111
PROG: lgame
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int convert(const string &s) {
	int len = (int)s.length();
	int total = 0;
	for (int i = 0; i < len; ++i) {
		switch (s[i]) {
		case 'q': 
			total += 7;
			break;
		case 'w':
			total += 6;
			break;
		case 'e':
			total += 1;
			break;
		case 'r':
			total += 2;
			break;
		case 't':
			total += 2;
			break;
		case 'y':
			total += 5;
			break;
		case 'u':
			total += 4;
			break;
		case 'i':
			total += 1;
			break;
		case 'o':
			total += 3;
			break;
		case 'p':
			total += 5;
			break;
		case 'a':
			total += 2;
			break;
		case 's':
			total += 1;
			break;
		case 'd':
			total += 4;
			break;
		case 'f':
			total += 6;
			break;
		case 'g':
			total += 5;
			break;
		case 'h':
			total += 5;
			break;
		case 'j':
			total += 7;
		case 'k':
			total += 6;
			break;
		case 'l':
			total += 3;
			break;
		case 'z':
			total += 7;
			break;
		case 'x':
			total += 7;
			break;
		case 'c':
			total += 4;
			break;
		case 'v':
			total += 6;
			break;
		case 'b':
			total += 5;
			break;
		case 'n':
			total += 2;
			break;
		case 'm':
			total += 5;
			break;
		}
	}
	return total;
}

int main() {
	ofstream fout("lgame.out");
	ifstream fin("lgame.in");
	ifstream din("lgame.dict");
	string s;
	fin >> s;
	int sSize = (int)s.length();
	
	vector<string> dictionary;
	string ds;
	din >> ds;
	while (ds != ".") {
		dictionary.push_back(ds);
		din >> ds;
	}
	int dictSize = (int)dictionary.size();
	
	vector<int> dictionaryVals(dictSize);
	for (int a = 0; a < dictSize; ++a) {
		dictionaryVals[a] = convert(dictionary[a]);
	}

	int bestVal = 0;
	vector<string> bestStrings;
	for (int i = 0; i < dictSize; ++i) { // for every word in the dictionary
		// check if we can make this word
		int wordLength = (int)dictionary[i].length();
		vector<bool> used(sSize, false);
		bool wordMatched = true;
		for (int j = 0; j < wordLength; ++j) { // for every character in this word
			bool matched = false;
			for (int k = 0; k < sSize; ++k) { // for every character in s
				// see if the character in the word matches the character in s
				if (!used[k]) { // if we haven't already used this character
					if (dictionary[i][j] == s[k]) { // if they match
						matched = true;
						used[k] = true;
						break;
					}
				}
			}
			if (!matched) { // we didn't find anything that matched
				wordMatched = false;
				break;
			}
		}
		if (wordMatched) { // we were able to make this word
			if (dictionaryVals[i] > bestVal) { // this is better than the current best
				bestVal = dictionaryVals[i];
				bestStrings.clear();
				bestStrings.push_back(dictionary[i]);
			}
			else if (dictionaryVals[i] == bestVal) { // this is the same as the current best
				bestStrings.push_back(dictionary[i]);
			}
		}
	}

	cout << bestVal << endl;
	for (int x = 0; x < (int)bestStrings.size(); ++x) {
		cout << bestStrings[x] << endl;
	}
	return 0;
}