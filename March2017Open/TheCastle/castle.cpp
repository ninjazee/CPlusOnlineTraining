/*
ID: kml111
PROG: castle
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printGrid(const vector<vector<bool>> &horizontal, const vector<vector<bool>> &vertical) {
	int n = (int)vertical.size();
	int m = (int)horizontal[0].size();
	for (int y = 0; y <= (n * 2); ++y) { // for each row
		for (int z = 0; z <= (m * 2); ++z) { // for each column
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
			else { // it is a vertical row
				if (z % 2 == 0) { // there may or may not be a vertical road here
					if (vertical[y / 2][z / 2]) {
						cout << '|';
					}
					else {
						cout << ' ';
					}
				}
				else {
					cout << ' ';
				}
			}
		}
		cout << endl;
	}
}

int main() {
	ofstream fout("castle.out");
	ifstream fin("castle.in");
	int m, n;
	fin >> m >> n;
	
	//int wallint[] = { 1, 2, 4, 8 };
	//vector<int> walls(wallint, wallint + sizeof(wallint) / sizeof(int));

	vector<vector<bool>> horizontal(n + 1, vector<bool>(m, false));
	vector<vector<bool>> vertical(n, vector<bool>(m + 1, false));
	for (int a = 0; a < n; ++a) {
		for (int b = 0; b < m; ++b) {
			int x;
			fin >> x;
			
			if ((1 & x) != 0) {
				vertical[a][b] = true;
			}
			if ((2 & x) != 0) {
				horizontal[a][b] = true;
			}
			if ((4 & x) != 0) {
				vertical[a][b + 1] = true;
			}
			if ((8 & x) != 0) {
				horizontal[a + 1][b] = true;
			}
		}
	}

	printGrid(horizontal, vertical);

	return 0;
}