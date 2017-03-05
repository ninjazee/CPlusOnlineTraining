#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void pickone(const tuple<int, int> &cow, const vector<vector<bool>> &horizontal, const vector<vector<bool>> &vertical) {
	
}

int main() {
	ofstream fout("countcross.out");
	ifstream fin("countcross.in");
	int n, k, r;
	fin >> n >> k >> r;

	vector<vector<bool>> horizontal(n + 1, vector<bool>(n, false));
	vector<vector<bool>> vertical(n + 1, vector<bool>(n, false));
	for (int x = 0; x < n; ++x) {
		horizontal[n][x] = true;
		vertical[n][x] = true;
		horizontal[0][x] = true;
		vertical[0][x] = true;
	}
	for (int a = 0; a < r; ++a) {
		int r, c, r1, c1;
		fin >> r >> c >> r1 >> c1;
		int minc = min()
		if (r == r1) {
			vertical[r1][c1] = true;
		}
		else {
			horizontal[r1][c1] = true;
		}
	}

	vector <tuple<int, int>> cows(k);
	for (int b = 0; b < k; ++b) {
		int r, c;
		fin >> r >> c;
		cows[b] = make_tuple(r, c);
	}

	for (int c = 0; c < k; ++c) {

	}
	return 0;
}
