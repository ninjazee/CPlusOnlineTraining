/*
ID: kml111
PROG: combo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool diff2(const int n, const int a, const int b) {
	int diff = ((a - b) + n) % n;
	return (diff <= 2 || diff >= n - 2);
}

int combinationLock(const int n, const vector<int> &fnums, const vector<int> &mnums) {
	int counter = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				if (diff2(n, i, fnums[0]) && diff2(n, j, fnums[1]) && diff2(n, k, fnums[2])) {
					counter += 1;
				}
				else if (diff2(n, i, mnums[0]) && diff2(n, j, mnums[1]) && diff2(n, k, mnums[2])) {
					counter += 1;
				}
			}
		}
	}

	return counter;
}

int main() {
	ofstream fout("combo.out");
	ifstream fin("combo.in");
	int n;
	fin >> n;
	vector<int> fnums(3);
	for (int x = 0; x < 3; ++x) {
		int fnum;
		fin >> fnum;
		fnums[x] = fnum;
	}
	vector<int> mnums(3);
	for (int y = 0; y < 3; ++y) {
		int mnum;
		fin >> mnum;
		mnums[y] = mnum;
	}

	fout << combinationLock(n, fnums, mnums) << endl;
	return 0;
}