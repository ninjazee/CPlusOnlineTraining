/*
ID: kml111
PROG: camelot
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int checkLocation(const int br, const int bc, const int currr, const int currc, const vector<tuple<int, int>> &knightpos, vector<vector<int>> &seen) {
	queue<tuple<int, int, int>> exam;
	// Push node 0 in 
	exam.push(make_tuple(currr, currc, 0));
	seen[currr][currc] = 0;

	while (!exam.empty()) {
		auto cur_tuple = exam.front();
		int r = get<0>(cur_tuple);
		int c = get<1>(cur_tuple);
		int moves = get<2>(cur_tuple);
		exam.pop();
		
		// Add next nodes. 
		if (r + 2 < br) { // we can go up
			if (c + 1 < bc) { // we can go right
				if (seen[r + 2][c + 1] == -1) { // we have not been here before
					seen[r + 2][c + 1] = moves + 1;
					exam.push(make_tuple(r + 2, c + 1, moves + 1));
				}
			}
			if (c - 1 >= 0) { // we can go left
				if (seen[r + 2][c - 1] == -1) { // we have not been here before
					seen[r + 2][c - 1] = moves + 1;
					exam.push(make_tuple(r + 2, c - 1, moves + 1));
				}
			}
		}
		if (r - 2 >= 0) { // we can go down
			if (c + 1 < bc) { // we can go right
				if (seen[r - 2][c + 1] == -1) { // we have not been here before
					seen[r - 2][c + 1] = moves + 1;
					exam.push(make_tuple(r - 2, c + 1, moves + 1));
				}
			}
			if (c - 1 >= 0) { // we can go left
				if (seen[r - 2][c - 1] == -1) { // we have not been here before
					seen[r - 2][c - 1] = moves + 1;
					exam.push(make_tuple(r - 2, c - 1, moves + 1));
				}
			}
		}
		if (c + 2 < bc) { // we can go right
			if (r + 1 < br) { // we can go up
				if (seen[r + 1][c + 2] == -1) { // we have not been here before
					seen[r + 1][c + 2] = moves + 1;
					exam.push(make_tuple(r + 1, c + 2, moves + 1));
				}
			}
			if (r - 1 >= 0) { // we can go down
				if (seen[r - 1][c + 2] == -1) { // we have not been here before
					seen[r - 1][c + 2] = moves + 1;
					exam.push(make_tuple(r - 1, c + 2, moves + 1));
				}
			}
		}
		if (c - 2 >= 0) { // we can go left
			if (r + 1 < br) { // we can go up
				if (seen[r + 1][c - 2] == -1) { // we have not been here before
					seen[r + 1][c - 2] = moves + 1;
					exam.push(make_tuple(r + 1, c - 2, moves + 1));
				}
			}
			if (r - 1 >= 0) { // we can go down
				if (seen[r - 1][c - 2] == -1) { // we have not been here before
					seen[r - 1][c - 2] = moves + 1;
					exam.push(make_tuple(r - 1, c - 2, moves + 1));
				}
			}
		}
	}

	int retVal = 0;
	for (int i = 0; i < (int)knightpos.size(); ++i) {
		retVal += seen[get<0>(knightpos[i])][get<1>(knightpos[i])];
	}
	
	return retVal;
}

int main() {
	ofstream fout("camelot.out");
	ifstream fin("camelot.in");
	int r, c;
	fin >> r >> c;
	int kr;
	char kc;
	fin >> kc >> kr;
	tuple<int, int> kingpos = make_tuple(kr - 1, kc - 'A');

	vector<tuple<int, int>> knightpos;
	while (!fin.eof()) {
		int r;
		char c;
		fin >> c;
		if (fin.eof())
			break;
		fin >> r;
		knightpos.push_back(make_tuple(r - 1, c - 'A'));
	}

	
	int best = numeric_limits<int>::max();
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			vector<vector<int>> seen(r, vector<int>(c, -1));
			int curr = checkLocation(r, c, i, j, knightpos, seen);
			if (curr < best) {
				best = curr;
			}
		}
	}
	
	fout << best << endl;
	
	return 0;
}