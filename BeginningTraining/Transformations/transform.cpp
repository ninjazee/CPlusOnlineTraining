/*
ID: kml111
PROG: ride
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool areSame(const vector<string> &before, const vector<string> &after) {
	int n = (int)before.size();
	int i = 0;
	bool same = true;
	while (i < n && same) {
		if (before[i] != after[i]) {
			same = false;
		}
		i += 1;
	}
	return same;
}

int detectChange(const vector<string> &before, const vector<string> &after) {
	int retVal = 7;
	
	// check if both vectors are the same (no change, #6)
	if (areSame(before, after)) {
		retVal = 6;
	}

	return retVal;
}

int main() {
	ofstream fout("transform.out");
	ifstream fin("transform.in");
	int n;
	fin >> n;
	vector<string> before(n);
	for (int a = 0; a < n; ++a) {
		string line;
		fin >> line;
		before[a] = line;
	}
	vector<string> after(n);
	for (int b = 0; b < n; ++b) {
		string line;
		fin >> line;
		after[b] = line;
	}
	cout << detectChange(before, after) << endl;
	return 0;
}
