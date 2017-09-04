/*
ID: kml111
PROG: theme
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
	ofstream fout("theme.out");
	ifstream fin("theme.in");
	int n;
	fin >> n;
	vector<int> noteSequence(n);
	for (int a = 0; a < n; ++a) {
		int note;
		fin >> note;
		noteSequence[a] = note;
	}

	vector<int> differences(n - 1);
	for (int i = 1; i < n; ++i) {
		differences[i - 1] = noteSequence[i] - noteSequence[i - 1];
	}

	/*
	unordered_map<string, int> seen;
	int longestTheme = 0;
	string lTheme;
	for (int i = 0; i < n - 1; ++i) {
		string recordString;
		for (int j = i; j < n - 1; ++j) {
			recordString.push_back((char)(differences[j] + 88));
			auto found = seen.find(recordString);
			if (found == seen.end()) { // we haven't seen this one before
				int location = i * 100000 + j;
				seen.insert(make_pair(recordString, location));
			}
			else { // we have seen this one before
				// if it's not an overlap
				int rsLength = (int)recordString.length();
				if (rsLength >= 5) {
					if ((found->second) % 100000 < i - 1) {
						if (longestTheme < rsLength) {
							longestTheme = rsLength;
							lTheme = recordString;
						}
					}
				}
			}
		}
	}
	*/

	int longestTheme = 0;
	//string lTheme;
	for (int i = 0; i < n - 1; ++i) { // starting point of first string
		for (int j = i + 4; j < n - 4; ++j) { // starting point of second string
			int maxK = min(j - i - 1, n - 1 - j);
			for (int k = 0; k < maxK; ++k) { // length of strings
				if (differences[i + k] != differences[j + k]) {
					break;
				}
				else {
					if ((k + 1) >= 4) {
						if ((k + 1) > longestTheme) {
							longestTheme = k + 1;
						}
					}
				}
			}
		}
		if (longestTheme >= (n - i) / 2)
		{
			break;
		}
	}

	if (longestTheme + 1 >= 5) {
		fout << longestTheme + 1 << endl;
	}
	else {
		fout << 0 << endl;
	}
	return 0;
}