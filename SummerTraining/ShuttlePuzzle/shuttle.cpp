/*
ID: kml111
PROG: shuttle
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool DFS(const string current, vector<int> &moves, const string &goal, const int gapHole) {
	if (current == goal) // we got to the end!
		return true;
	else {
		int boardSize = (int)current.length();
		bool endReach = false;
		for (int i = 0; i < 4; ++i) { // for each of the four options
			if (i == 0) { // jump a white marble over a black marble into the hole (from the left)
				if (gapHole - 2 >= 0) { // there is actually a hole there
					if (current[gapHole - 2] == 'W' && current[gapHole - 1] == 'B') { // if there is a white and a black marble
						// try it
						string newString = current;
						newString[gapHole - 2] = ' '; // this becomes the new gap
						newString[gapHole] = 'W'; // we moved the white marble into the gap
						moves.push_back(gapHole - 2);
						if (DFS(newString, moves, goal, gapHole - 2)) { // this combination worked!
							endReach = true;
							break;
						}
					}
				}
			}
			else if (i == 1) { // move a white marble into the hole (from the left)
				if (gapHole - 1 >= 0) { // there is actually a hole there
					if (current[gapHole - 1] == 'W') { // if it is a white marble
						// try it
						string newString = current;
						newString[gapHole - 1] = ' '; // this becomes the new gap
						newString[gapHole] = 'W'; // we moved the white marble into the gap
						moves.push_back(gapHole - 1);
						if (DFS(newString, moves, goal, gapHole - 1)) { // this combination worked!
							endReach = true;
							break;
						}
					}
				}
			}
			else if (i == 2) { // move a black marble into the hole (from the right)
				if (gapHole + 1 < boardSize) { // there is actually a hole there
					if (current[gapHole + 1] == 'B') { // if it is a black marble
						// try it
						string newString = current;
						newString[gapHole + 1] = ' '; // this becomes the new gap
						newString[gapHole] = 'B'; // we moved the black marble into the gap
						moves.push_back(gapHole + 1);
						if (DFS(newString, moves, goal, gapHole + 1)) { // this combination worked!
							endReach = true;
							break;
						}
					}
				}
			}
			else { // jump a black marble over a white marble into the hole (from the right)
				if (gapHole + 2 < boardSize) { // there is actually a hole there
					if (current[gapHole + 2] == 'B') { // if it is a black marble
						// try it
						string newString = current;
						newString[gapHole + 2] = ' '; // this becomes the new gap
						newString[gapHole] = 'B'; // we moved the black marble into the gap
						moves.push_back(gapHole + 2);
						if (DFS(newString, moves, goal, gapHole + 2)) { // this combination worked!
							endReach = true;
							break;
						}
					}
				}
			}
		}
		if (endReach == false) { // this setting of the board doesn't work
			moves.pop_back();
		}
		return endReach;
	}
}

int main() {
	ofstream fout("shuttle.out");
	ifstream fin("shuttle.in");
	int n;
	fin >> n;

	string goal;
	for (int i = 0; i < n; ++i) {
		goal.push_back('B');
	}
	goal.push_back(' ');
	for (int j = 0; j < n; ++j) {
		goal.push_back('W');
	}

	string current;
	for (int k = 0; k < n; ++k) {
		current.push_back('W');
	}
	current.push_back(' ');
	for (int l = 0; l < n; ++l) {
		current.push_back('B');
	}

	vector<int> moves;
	bool worked = DFS(current, moves, goal, n);

	int counter = 1;
	fout << moves[0] + 1;
	for (int i = 1; i < (int)moves.size(); ++i) {
		if (counter == 20) {
			fout << endl;
			counter = 0;
			fout << moves[i] + 1;
		}
		else {
			fout << " " << moves[i] + 1;
		}
		counter += 1;
	}
	fout << endl;
	return 0;
}