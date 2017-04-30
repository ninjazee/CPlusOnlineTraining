/*
ID: kml111
PROG: ttwo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>

using namespace std;

int encode(const int fr, const int fc, const int fd, const int cr, const int cc, const int cd) {
	return fr << 16 | fc << 12 | fd << 10 | cr << 6 | cc << 2 | cd;
}

int dx[4] = {0, 1, 0, -1};
int dy[4] = { -1, 0, 1, 0 };

int tamworthTwo(const vector<vector<bool>> &grid, unordered_set<int> &record, tuple<int, int, int, int, int, int> &pos) {
	int minutes = 0;
	while ((get<0>(pos) != get<3>(pos)) || (get<1>(pos) != get<4>(pos))) { // farmer john has not met the cows
		int code = encode(get<0>(pos), get<1>(pos), get<2>(pos), get<3>(pos), get<4>(pos), get<5>(pos));
		if (record.find(code) != record.end()) { // already been in this state, going to loop infinitely
			return 0;
		}
		else {
			record.insert(code); // add this position to the record
			// farmer john moves
			if (get<2>(pos) == 0) { // facing north
				if (get<0>(pos) == 0 || grid[get<0>(pos) - 1][get<1>(pos)] == true) { // bumped into an obstacle/wall
					get<2>(pos) = 1; // turn to the east
				}
				else { // nothing in the way
					get<0>(pos) -= 1; // move north
				}
			}
			else if (get<2>(pos) == 1) { // facing east
				if (get<1>(pos) == 9 || grid[get<0>(pos)][get<1>(pos) + 1] == true) { // bumped into an obstacle/wall
					get<2>(pos) = 2; // turn to the south
				}
				else { // nothing in the way
					get<1>(pos) += 1; // move east
				}
			}
			else if (get<2>(pos) == 2) { // facing south
				if (get<0>(pos) == 9 || grid[get<0>(pos) + 1][get<1>(pos)] == true) { // bumped into an obstacle/wall
					get<2>(pos) = 3; // turn to the west
				}
				else { // nothing in the way
					get<0>(pos) += 1; // move south
				}
			}
			else if (get<2>(pos) == 3) { // facing west
				if (get<1>(pos) == 0 || grid[get<0>(pos)][get<1>(pos) - 1] == true) { // bumped into an obstacle/wall
					get<2>(pos) = 0; // turn to the north
				}
				else { // nothing in the way
					get<1>(pos) -= 1; // move west
				}
			}

			// cows move
			if (get<5>(pos) == 0) { // facing north
				if (get<3>(pos) == 0 || grid[get<3>(pos) - 1][get<4>(pos)] == true) { // bumped into an obstacle/wall
					get<5>(pos) = 1; // turn to the east
				}
				else { // nothing in the way
					get<3>(pos) -= 1; // move north
				}
			}
			else if (get<5>(pos) == 1) { // facing east
				if (get<4>(pos) == 9 || grid[get<3>(pos)][get<4>(pos) + 1] == true) { // bumped into an obstacle/wall
					get<5>(pos) = 2; // turn to the south
				}
				else { // nothing in the way
					get<4>(pos) += 1; // move east
				}
			}
			else if (get<5>(pos) == 2) { // facing south
				if (get<3>(pos) == 9 || grid[get<3>(pos) + 1][get<4>(pos)] == true) { // bumped into an obstacle/wall
					get<5>(pos) = 3; // turn to the west
				}
				else { // nothing in the way
					get<3>(pos) += 1; // move south
				}
			}
			else if (get<5>(pos) == 3) { // facing west
				if (get<4>(pos) == 0 || grid[get<3>(pos)][get<4>(pos) - 1] == true) { // bumped into an obstacle/wall
					get<5>(pos) = 0; // turn to the north
				}
				else { // nothing in the way
					get<4>(pos) -= 1; // move west
				}
			}

			minutes += 1; // time passed
		}
	}
	return minutes;
}

int main() {
	ofstream fout("ttwo.out");
	ifstream fin("ttwo.in");
	vector<vector<bool>> grid(10, vector<bool>(10, false)); // record of where obstacles are
	int fr, fc, fd, cr, cc, cd;
	for (int a = 0; a < 10; ++a) { // read each row
		string row;
		fin >> row;
		for (int b = 0; b < 10; ++b) { // read each char
			if (row[b] == '*') { // there is an obstacle here
				grid[a][b] = true;
			}
			else if (row[b] == 'F') { // farmer john is here
				fr = a;
				fc = b;
				fd = 0; // 0 = north, 1 = east, 2 = south, 3 = west
			}
			else if (row[b] == 'C') { // the cows are here
				cr = a;
				cc = b;
				cd = 0; // 0 = north, 1 = east, 2 = south, 3 = west
			}
		}
	}
	tuple<int, int, int, int, int, int> pos = make_tuple(fr, fc, fd, cr, cc, cd);
	unordered_set<int> record;
	int code = encode(fr, fc, fd, cr, cc, cd);
	//record.insert(code);

	int fcode = encode(4, 5, 0, 7, 2, 0);
	int ocode = encode(1, 4, 1, 7, 5, 2);
	fout << tamworthTwo(grid, record, pos) << endl;
	return 0;
}