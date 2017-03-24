/*
ID: kml111
PROG: frac1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool compareTuple(const pair<int, int> &p1, const pair<int, int> &p2) {
	return ((p1.first * p2.second) < (p1.second * p2.first)); // use cross multiplication
}

int GCD(int u, int v) {
	while (v != 0) {
		int r = u % v;
		u = v;
		v = r;
	}
	return u;
}

void orderedFractions(const int n, vector<pair<int, int>> &fractions) {
	// add 0/1 and 1/1 to the list because they will always be in the list
	fractions.push_back(make_pair(0, 1)); 
	fractions.push_back(make_pair(1, 1));

	for (int i = 2; i < n + 1; ++i) { // for every denominator less than n
		for (int j = 1; j < i; ++j) { // for every numerator
			if (GCD(j, i) == 1) { // if it cannot be simplified
				fractions.push_back(make_pair(j, i));
			}
		}
	}

	sort(fractions.begin(), fractions.end(), compareTuple);
}

int main() {
	ofstream fout("frac1.out");
	ifstream fin("frac1.in");
	int n;
	fin >> n;
	vector<pair<int, int>> fractions;
	orderedFractions(n, fractions);

	for (int a = 0; a < (int)fractions.size(); ++a) {
		fout << fractions[a].first << '/' << fractions[a].second << endl;
	}
	return 0;
}