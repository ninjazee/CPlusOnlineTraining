#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printGrid(const vector<vector<int>> &grid) {
	int n = (int)grid.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << grid[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << "-----------------------------------------" << endl;
}
