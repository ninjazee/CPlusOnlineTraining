/*
ID: kml111
PROG: castle
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

int followGraph(const vector<vector<bool>> &horizontal, const vector<vector<bool>> &vertical, vector<vector<bool>> &reached, const int currentr, const int currentc) {
	if (reached[currentr][currentc]) // if already reached this square it will not lead you anywhere
		return 0;
	else {
		reached[currentr][currentc] = true;
		int count = 1;

		if (vertical[currentr][currentc + 1] == false) { // there is not a wall to the right; going right: c + 1
			count += followGraph(horizontal, vertical, reached, currentr, currentc + 1);
		}
		if (vertical[currentr][currentc] == false) { // There is not a wall to the left; going left: c - 1
			count += followGraph(horizontal, vertical, reached, currentr, currentc - 1);
		}
		if (horizontal[currentr + 1][currentc] == false) { // there is not a wall above; going up: r + 1
			count += followGraph(horizontal, vertical, reached, currentr + 1, currentc);
		}
		if (horizontal[currentr][currentc] == false) { // there is not a wall underneath; going down: r - 1
			count += followGraph(horizontal, vertical, reached, currentr - 1, currentc);
		}

		return count;
	}
}

int main() {
	ofstream fout("castle.out");
	ifstream fin("castle.in");
	int m, n;
	fin >> m >> n;
	
	//int wallint[] = { 1, 2, 4, 8 };
	//vector<int> walls(wallint, wallint + sizeof(wallint) / sizeof(int));

	// read in map of castle
	vector<vector<bool>> horizontal(n + 1, vector<bool>(m, false));
	vector<vector<bool>> vertical(n, vector<bool>(m + 1, false));
	for (int a = 0; a < n; ++a) { // for every row
		for (int b = 0; b < m; ++b) { // for every square
			int x;
			fin >> x;
			
			if ((1 & x) != 0) { // there is a wall to the west
				vertical[a][b] = true;
			}
			if ((2 & x) != 0) { // there is a wall to the north
				horizontal[a][b] = true;
			}
			if ((4 & x) != 0) { // there is a wall to the east
				vertical[a][b + 1] = true;
			}
			if ((8 & x) != 0) { // there is a wall to the south
				horizontal[a + 1][b] = true;
			}
		}
	}

	printGrid(horizontal, vertical);

	vector<vector<bool>> reached(n, vector<bool>(m, false));

	// figure out how big the rooms are and how many rooms there are
	vector<int> rooms;
	for (int x = 0; x < n; ++x) { // for each row
		for (int y = 0; y < m; ++y) { // for each square
			int roomSize = followGraph(horizontal, vertical, reached, x, y);
			if (roomSize != 0) { // there is a room
				rooms.push_back(roomSize);
			}
		}
	}

	sort(rooms.begin(), rooms.end());

	cout << (int)rooms.size() << endl << rooms[(int)rooms.size() - 1] << endl;

	return 0;
}