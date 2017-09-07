/*
ID: kml111
PROG: sub

LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ofstream fout("subset.out");
	ifstream fin("subset.in");
	int n;
	fin >> n;
	if ((((n * n + n) / 2) % 2) == 0) { // works
		int m = (n * n + n) / 4;
		vector<vector<long long>> combinations(n + 1, vector<long long>(m + 1, 0));
		combinations[0][0] = 1;

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				combinations[i][j] = combinations[i - 1][j];
				if (j >= i)
					combinations[i][j] += combinations[i - 1][j - i];
			}
		}

		fout << combinations[n][m] / 2 << endl;
	}
	else { // doesn't work
		fout << 0 << endl;
	}
	return 0;
}