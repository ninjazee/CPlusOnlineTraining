/*
ID: kml111
PROG: sub

LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int combination(const int a, const int b) { // a is the number of items you have to use, b is the total.
	if (a == 0) {
		if (b == 0) {
			// there is one way to make 0 with 0 items
			return 1;
		}
		else if (b > 0) {
			// there is no way to make anything larger than 0 with 0 items
			return 0;

		}
	}
	else if (a >= 1) {
		if (b < a) {
			// there is no way to go here, look at one before
			return combination(a - 1, b);
		}
		else if (b >= a) {
			// look at one before and see if there are any more
			return combination(a - 1, b) + combination(a - 1, b - a);
		}
	}
}

long long combination2(const int a, const int b, vector<vector<long long>> &combinations) { // a is the number of items you have to use, b is the total
	if (combinations[a][b] != -1) {
		return combinations[a][b];
	}
	else {
		long long retVal;
		if (a == 0) {
			if (b == 0) {
				// there is one way to make 0 with 0 items
				retVal = 1;
			}
			else if (b > 0) {
				// there is no way to make anything larger than 0 with 0 items
				retVal = 0;

			}
		}
		else if (a >= 1) {
			if (b < a) {
				// there is no way to go here, look at one before
				retVal = combination2(a - 1, b, combinations);
			}
			else if (b >= a) {
				// look at one before and see if there are any more
				retVal = combination2(a - 1, b, combinations) + combination2(a - 1, b - a, combinations);
			}
		}
		combinations[a][b] = retVal;
		return retVal;
	}
}

int main2() {
	ofstream fout("subset.out");
	ifstream fin("subset.in");
	int n;
	fin >> n;
	if ((((n * n + n) / 2) % 2) == 0) { // works
		int m = (n * n + n) / 4;
		vector<vector<long long>> combinations(n + 1, vector<long long>(m + 1, -1));
		fout << combination2(n, m, combinations) / 2 << endl;
	}
	else { // doesn't work
		fout << 0 << endl;
	}
	return 0;
}

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