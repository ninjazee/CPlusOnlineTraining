/*
ID: kml111
PROG: contact
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

bool compareTuple(const pair<string, int> &p1, const pair<string, int> &p2) {
	if (p1.second > p2.second) { // if the second is smaller than the first (sorted order)
		return true;
	}
	else if (p1.second < p2.second) { // if the first is smaller than the second (not sorted order)
		return false;
	}
	else { // they have the same frequency
		int l1 = (int)(p1.first).length();
		int l2 = (int)(p2.first).length();
		if (l1 < l2) { // the second is longer than the first (sorted order)
			return true;
		}
		else if (l1 > l2) { // the second is longer than the first (sorted order)
			return false;
		}
		else { // they are the same length
			return (p1.first < p2.first); // return if the binary number is smaller (sorted) or bigger (not sorted)
		}
	}
}

int main() {
	ofstream fout("contact.out");
	ifstream fin("contact.in");
	ostream &out = fout; 
	int a, b, n;
	fin >> a >> b >> n;
	stringstream seqStr;
	while (!fin.eof()) {
		string line;
		getline(fin, line);
		seqStr << line;
	}
	string sequence = seqStr.str();

	unordered_map<string, int> patterns;
	int len = (int)sequence.length();
	for (int i = 0; i < len; ++i) { // for every character/bit in the sequence
		for (int j = a; j <= b; ++j) { // for each possible size of pattern
			if (i + j <= len) { // if it fits in the string
				string pattern = sequence.substr(i, j); // pattern which we are working with
				auto got = patterns.find(pattern);
				if (got == patterns.end()) { // not already in the map
					// add it
					patterns[pattern] = 1;
				}
				else { // already in the map
					got->second += 1;
				}
			}
			else {
				break; // we cannot make anymore strings with this place so we break
			}
		}
	}

	vector<pair<string, int>> patternList; // move the unordered_map to a vector
	for (pair<string, int> a : patterns) {
		patternList.push_back(a);
	}

	sort(patternList.begin(), patternList.end(), compareTuple); // sort the vector

	int pointer = 0; // place where we are
	int numPatterns = (int)patternList.size();
	for (int x = 0; x < n; ++x) {
		if (pointer >= numPatterns) {
			break;
		}
		if (get<1>(patternList[pointer]) == 0) {
			break;
		}
		out << get<1>(patternList[pointer]) << endl;
		out << get<0>(patternList[pointer]);
		int count = 1;
		while (pointer + 1 < numPatterns && get<1>(patternList[pointer]) == get<1>(patternList[pointer + 1])) { // while patterns have the same frequency
			pointer += 1;
			if (count == 6) {
				out << endl;
				count = 0;
				out << get<0>(patternList[pointer]);
			}
			else {
				out << ' ' << get<0>(patternList[pointer]);
			}
			count += 1;
		}
		pointer += 1;
		out << endl;
	}
	return 0;
}