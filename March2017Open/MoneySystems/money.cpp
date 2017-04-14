/*
ID: kml111
PROG: money
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ofstream fout("money.out");
	ifstream fin("money.in");
	int v, n;
	fin >> v >> n;
	vector<int> coins(v);
	for (int a = 0; a < v; ++a) {
		int coin;
		fin >> coin;
		coins[a] = coin;
	}

	vector<vector<long long>> combinations(v + 1, vector<long long>(n + 1, 0));
	for (int b = 0; b <= v; ++b) {
		combinations[b][0] = 1; // one way to construct 0 with any number of coins
	}
	
	for (int i = 1; i <= v; ++i) { // for every number of coins
		for (int j = 1; j <= n; ++j) { // for every possible value
			for (int k = 0; k <= j / coins[i - 1]; ++k) { // for every number of this coin that is less than the value
				// add the amount of possibilities of the remaining value when the value of the current coin is subtracted
				combinations[i][j] += combinations[i - 1][j - (k * coins[i - 1])];
			}
		}
	}
	fout << combinations[v][n] << endl;
	return 0;
}