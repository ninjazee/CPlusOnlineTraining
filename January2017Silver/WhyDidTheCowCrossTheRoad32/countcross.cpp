#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void printGrid(const vector<vector<bool>> &horizontal, const vector<vector<bool>> &vertical, const vector<vector<bool>> &cows) {
	int n = (int)vertical.size();
	for (int y = (n * 2); y >= 0; --y) { // for each row
		for (int z = 0; z < (n * 2) + 1; ++z) { // for each column
			if (y % 2 == 0) { // if it is a "horizontal" row
				if (z % 2 == 0) { // this is a corner
					cout << '+';
				}
				else { // there may or may not be a horizontal road here
					if (horizontal[y / 2][z / 2]) {
						cout << '-';
					}
					else {
						cout << ' ';
					}
				}
			}
			else { // it is a vertical/cow row
				if (z % 2 == 0) { // there may or may not be a vertical road here
					if (vertical[y / 2][z / 2]) {
						cout << '|';
					}
					else {
						cout << ' ';
					}
				}
				else { // there may or may not be a cow here
					if (cows[y / 2][z / 2]) {
						cout << '*';
					}
					else {
						cout << ' ';
					}
				}
			}
		}
		cout << endl;
	}
}

void pickone(const tuple<int, int> &cow, const vector<vector<bool>> &horizontal, const vector<vector<bool>> &vertical) {
	
}

int main() {
	ofstream fout("countcross.out");
	ifstream fin("countcross.in");
	int n, k, r;
	fin >> n >> k >> r;

	vector<vector<bool>> horizontal(n + 1, vector<bool>(n, false));
	vector<vector<bool>> vertical(n, vector<bool>(n + 1, false));
	for (int x = 0; x < n; ++x) {
		horizontal[n][x] = true;
		vertical[x][n] = true;
		horizontal[0][x] = true;
		vertical[x][0] = true;
	}
	for (int a = 0; a < r; ++a) {
		int r, c, r1, c1;
		fin >> r >> c >> r1 >> c1;
		int minc = min(c, c1);
		int minr = min(r, r1);
		if (r == r1) {
			vertical[minr - 1][minc] = true;
		}
		else {
			horizontal[minr][minc - 1] = true;
		}
	}

	vector<vector<bool>> cows(n, vector<bool>(n, false));
	for (int b = 0; b < k; ++b) {
		int r, c;
		fin >> r >> c;
		cows[r - 1][c - 1] = true;
	}
	/*
	vector <tuple<int, int>> cows(k);
	for (int b = 0; b < k; ++b) {
		int r, c;
		fin >> r >> c;
		cows[b] = make_tuple(r, c);
	}
	*/

	/*
	cout << "Cows:" << endl;
	for (int c = 0; c < k; ++c) {
		cout << get<0>(cows[c]) << ' ' << get<1>(cows[c]) << endl;
	}
	cout << endl << "Horizontal Roads:" << endl;
	for (int d = 0; d < (int)horizontal.size(); d++) {
		for (int e = 0; e < n; ++e) {
			cout << d << ' ' << e << horizontal[d][e] << endl;
		}
	}
	cout << "Vertical Roads:" << endl;
	for (int d = 0; d < (int)horizontal.size(); d++) {
		for (int e = 0; e < n; ++e) {
			cout << d << ' ' << e << horizontal[d][e] << endl;
		}
	}
	*/

	printGrid(horizontal, vertical, cows);
	return 0;
}
