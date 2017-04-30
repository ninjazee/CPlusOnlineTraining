/*
ID: kml111
PROG: maze1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

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
	ofstream fout("maze1.out");
	ifstream fin("maze1.in");
	int w, h;
	fin >> w >> h;

	vector<vector<bool>> horizontal(h + 1, vector<bool>(w, false)); // all of the horizontal walls
	vector<vector<bool>> vertical(h, vector<bool>(w + 1, false)); // all of the vertical walls
	int ex1r = -1, ex1c = -1, ex2r = -1, ex2c = -1;
	queue<tuple<int, int, int>> curr;
	for (int a = 0; a <= h * 2; ++a) { // for each row
		string row;
		while (!fin.eof() && row.size()<=0)
			getline(fin, row);
		if (row.size() <= 0)
			break; 
		for (int b = 0; b <= w * 2; ++b) { // for each column
			if (a % 2 == 0) { // if it is a "horizontal" row
				if (b % 2 != 0) { // this is not a corner
					if (row[b] == '-') { // there is a wall here
						horizontal[a / 2][b / 2] = true;
					}
					else { // there is not a wall here
						if (a == 0) { // this is an exit
							curr.push(make_tuple(a / 2, b / 2, 1));
						}
						else if (a == h * 2) {
							curr.push(make_tuple(a / 2 - 1, b / 2, 1));
						}
					}
				}
			}
			else { // it is a vertical row
				if (b % 2 == 0) { // there may or may not be a vertical road here
					if (row[b] == '|') { // there is a wall here
						vertical[a / 2][b / 2] = true;
					}
					else { // there is not a wall here
						if (b == 0) { // this is an exit
							curr.push(make_tuple(a / 2, b / 2, 1));
						}
						else if (b == w * 2) {
							curr.push(make_tuple(a / 2, b / 2 - 1, 1));
						}
					}
				}
			}
		}
	}

	vector<vector<int>> grid(h, vector<int>(w, 0));

	while (!curr.empty()) {
		auto curr_tuple = curr.front();
		curr.pop();
		int r = get<0>(curr_tuple);
		int c = get<1>(curr_tuple);
		int level = get<2>(curr_tuple);
		if (r < 0 || c < 0 || r >= h || c >= w) {
			continue;
		}
		if (grid[r][c] != 0) {
			continue;
		}
		grid[r][c] = level;

		// look at the square above
		if (!horizontal[r][c]) { // no wall above
			curr.push(make_tuple(r - 1, c, level + 1));
		}
		// look at the square to the left
		if (!vertical[r][c]) { // no wall to the left
			curr.push(make_tuple(r, c - 1, level + 1));
		}
		// look at the square underneath
		if (!horizontal[r + 1][c]) {
			curr.push(make_tuple(r + 1, c, level + 1));
		}
		// look at the square to the right
		if (!vertical[r][c + 1]) {
			curr.push(make_tuple(r, c + 1, level + 1));
		}
	}

	int biggest = 0;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (grid[i][j] > biggest) {
				biggest = grid[i][j];
			}
		}
	}

	//printGrid(horizontal, vertical);

	fout << biggest << endl;
	return 0;
}