/*
ID: kml111
PROG: barn1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int barnRepair(const int m, const int s, vector<int> &cows) {
	sort(cows.begin(), cows.end());
	int ret = s;
	vector<int> gaps;
	for (int i = 0; i < (int)cows.size() - 1; ++i) {
		gaps.push_back(cows[i + 1] - cows[i]);
	}
	sort(gaps.begin(), gaps.end());
	for (int j = 0; j < m - 1; ++j) {
		if ((int)gaps.size() - j - 1 < 0) {
			break;
		}
		else {
			ret -= gaps[(int)gaps.size() - j - 1] - 1;
		}
	}
	ret -= cows[0] - 1;
	ret -= s - cows[(int)cows.size() - 1];
	return ret;
}

int main() {
	ofstream fout("barn1.out");
	ifstream fin("barn1.in");
	int m, s, c;
	fin >> m >> s >> c;
	vector<int> cows(c);
	for (int x = 0; x < c; ++x) {
		int cow;
		fin >> cow;
		cows[x] = cow;
	}
	fout << barnRepair(m, s, cows) << endl;
	return 0;
}