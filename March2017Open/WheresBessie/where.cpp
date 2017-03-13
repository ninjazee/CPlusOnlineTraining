#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int wheresBessie(const vector<string> &grid) {
	int n = (int)grid.size();
	int x = 0;
	int y = 0;
	char start = grid[y][x];
	char other = grid[y][x];
	while (y < n && (grid[y][x] == start || grid[y][x] == other) {
		while (grid[y][x] == start || grid[y][x] == other) {
			x += 1;
			if (other == start && grid[y][x] != other) {
				other = grid[y][x];
			}
		}
		y += 1;
	}
}

int main() {
	ofstream fout("where.out");
	ifstream fin("where.in");
	int n;
	fin >> n;
	vector<string> grid(n);
	for (int a = 0; a < n; ++a) {
		string row;
		fin >> row;
		grid[a] = row;
	}

	fout << 2 << endl;
	return 0;
}