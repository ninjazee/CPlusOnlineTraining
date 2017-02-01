/*
ID: kml111
PROG: combo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int combinationLock(const int n, const vector<int> &fnums, const vector<int> &mnums) {
	int diff1 = abs(fnums[0] - mnums[0]);
	int diff2 = abs(fnums[1] - mnums[1]);
	int diff3 = abs(fnums[2] - mnums[2]);

	int multi1 = ((diff1 / 2) - 2) + 1;
	int multi2 = ((diff2 / 2) - 2) + 1;
	int multi3 = ((diff3 / 2) - 2) + 1;

	return (250 - (multi1 * multi2 * multi3));
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