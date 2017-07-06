/*
ID: kml111
PROG: nuggets
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ofstream fout("nuggets.out");
	ifstream fin("nuggets.in");
	int n;
	fin >> n;
	vector<int> options(n);
	for (int a = 0; a < n; ++a) {
		int i;
		fin >> i;
		options[a] = i;
	}

	vector<bool> works(2000001, false);
	for (int b = 0; b < n; ++b) {
		works[options[b]] = true;
	}

	for (int i = 0; i <= 2000000; ++i) {
		if (works[i]) {
			for (int j = 0; j < n; ++j) {
				if (i + options[j] <= 2000000) {
					works[i + options[j]] = true;
				}
			}
		}
	}

	int last = 0;
	for (int c = 0; c <= 2000000; ++c) {
		if (!works[c]) {
			last = c;
		}
	}

	if (last > 1990000) {
		fout << 0 << endl;
	}
	else {
		fout << last << endl;
	}
	return 0;
}