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
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

#define LARGE_NUMBER 9000000

void checkLocation(const int br, const int bc, const int currr, const int currc, const vector<tuple<int, int>> &knightpos, vector<vector<int>> &seen) {
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
				if (seen[r + 2][c + 1] == LARGE_NUMBER) { // we have not been here before
					seen[r + 2][c + 1] = moves + 1;
					exam.push(make_tuple(r + 2, c + 1, moves + 1));
				}
			}
			if (c - 1 >= 0) { // we can go left
				if (seen[r + 2][c - 1] == LARGE_NUMBER) { // we have not been here before
					seen[r + 2][c - 1] = moves + 1;
					exam.push(make_tuple(r + 2, c - 1, moves + 1));
				}
			}
		}
		if (r - 2 >= 0) { // we can go down
			if (c + 1 < bc) { // we can go right
				if (seen[r - 2][c + 1] == LARGE_NUMBER) { // we have not been here before
					seen[r - 2][c + 1] = moves + 1;
					exam.push(make_tuple(r - 2, c + 1, moves + 1));
				}
			}
			if (c - 1 >= 0) { // we can go left
				if (seen[r - 2][c - 1] == LARGE_NUMBER) { // we have not been here before
					seen[r - 2][c - 1] = moves + 1;
					exam.push(make_tuple(r - 2, c - 1, moves + 1));
				}
			}
		}
		if (c + 2 < bc) { // we can go right
			if (r + 1 < br) { // we can go up
				if (seen[r + 1][c + 2] == LARGE_NUMBER) { // we have not been here before
					seen[r + 1][c + 2] = moves + 1;
					exam.push(make_tuple(r + 1, c + 2, moves + 1));
				}
			}
			if (r - 1 >= 0) { // we can go down
				if (seen[r - 1][c + 2] == LARGE_NUMBER) { // we have not been here before
					seen[r - 1][c + 2] = moves + 1;
					exam.push(make_tuple(r - 1, c + 2, moves + 1));
				}
			}
		}
		if (c - 2 >= 0) { // we can go left
			if (r + 1 < br) { // we can go up
				if (seen[r + 1][c - 2] == LARGE_NUMBER) { // we have not been here before
					seen[r + 1][c - 2] = moves + 1;
					exam.push(make_tuple(r + 1, c - 2, moves + 1));
				}
			}
			if (r - 1 >= 0) { // we can go down
				if (seen[r - 1][c - 2] == LARGE_NUMBER) { // we have not been here before
					seen[r - 1][c - 2] = moves + 1;
					exam.push(make_tuple(r - 1, c - 2, moves + 1));
				}
			}
		}
	}
	
	/*
	int retVal = 0;
	for (int i = 0; i < (int)knightpos.size(); ++i) {
		retVal += seen[get<0>(knightpos[i])][get<1>(knightpos[i])];
	}
	
	return retVal;
	*/
}

int main() {
	ofstream fout("camelot.out");
	ifstream fin("camelot.in");
	int r, c;
	fin >> r >> c;
	int kr;
	char kingc;
	fin >> kingc >> kr;
	kr -= 1;
	int kc = kingc - 'A';

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

	int nKnights = (int)knightpos.size();
	// create a record of distances (in moves) of knights to a specific spot
	vector<vector<vector<int>>> distKnightRecords(r, vector<vector<int>>(c, vector<int>(nKnights, 0)));
	vector<vector<vector<vector<int>>>> distRecords(r, vector<vector<vector<int>>>(c, vector<vector<int>>(r, vector<int>(c, 0))));
	for (int i = 0; i < r; ++i) { // for every row number
		for (int j = 0; j < c; ++j) { // for every column number
			vector<vector<int>> seen(r, vector<int>(c, LARGE_NUMBER));
			checkLocation(r, c, i, j, knightpos, seen);
			for (int k = 0; k < nKnights; k++)
				distKnightRecords[i][j][k] = seen[get<0>(knightpos[k])][get<1>(knightpos[k])];
			distRecords[i][j] = seen;
		}
	}
	
	int best = numeric_limits<int>::max();
	// try the distances of all of the meeting spots and all of the spots the king could go to
	for (int i = 0; i < r; ++i) { // meeting spot row
		for (int j = 0; j < c; ++j) { // meeting spot column
			int sum = 0; 
			for (int k = 0; k < nKnights; k++) // calculate the distance from all of the knights to the location
				sum += distKnightRecords[i][j][k];

			for (int k = 0; k < r; ++k) { // king meeting spot row
				for (int l = 0; l < c; ++l) { // king meeting spot column
					int sum1 = sum;
					sum1 += distRecords[i][j][k][l];
					// check the distance from the king meeting spot to the king
					int rdist = abs(k - kr);
					int cdist = abs(l - kc);
					sum1 += max(rdist, cdist);


					for (int p = 0; p < nKnights; p++) {
						int sum2 = sum1;
						// Knight p is redirected.
						sum2 -= distKnightRecords[i][j][p];
						sum2 += distKnightRecords[k][l][p];
						if (sum2 < best) {
							best = sum2;
						}
					}
				}
			}

		}
	}

	if (nKnights == 0) {
		fout << 0 << endl;
	}
	else {
		fout << best << endl;
	}
	return 0;
}