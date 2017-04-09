/*
ID: kml111
PROG: lamps
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

void pressButton (vector<int> &states) {
	int combinations = (int)states.size();
	//vector<int> currentStates(combinations, 0);
	vector<int> origStates(states);
	fill(states.begin(), states.end(), 0);
	// Calculate all possible states for this level.
	for (int i = 0; i < combinations; ++i) {
		if (origStates[i] != 0) { // a lamp is currently in this state
			// button 1 is pressed: all lamps change state
			states[i ^ 15] += 1; // 15 = 1111

			// button 2 is pressed: odd lamps change state
			states[i ^ 10] += 1; // 10 = 1010

			// button 3 is pressed: even lamps change state
			states[i ^ 5] += 1; // 5 = 0101

			// button 3 is pressed: every 3rd lamp changes state
			states[i ^ 9] += 1; // 9 = 1001
		}
	}
}

int main() {
	ofstream fout("lamps.out");
	ifstream fin("lamps.in");
	int n, c;
	fin >> n >> c;
	vector<int> onNums;
	int x;
	fin >> x;
	while (x != -1) {
		onNums.push_back(x);
		fin >> x;
	}
	vector<int> offNums;
	int y;
	fin >> y;
	while (y != -1) {
		offNums.push_back(y);
		fin >> y;
	}

	vector<int> states(16, 0);
	states[15] = 1;
	for (int i = 0; i < c; ++i) {
		pressButton(states);
		/*
		cout << "Press " << i + 1 << endl;
		for (int j = 0; j < (int)states.size(); ++j) {
			cout << bitset<4>(j) << ": " << states[j] << endl;
		}
		cout << endl;
		*/
	}

	for (int j = 0; j < (int)states.size(); ++j) {
		if (states[j] > 0) { // some lamps are in this state
			for (int a = 0; a < (int)onNums.size(); ++a) { // check if it fits the onNums criteria
				if ((onNums[a] % 6) == 0) {
					if ((j & 8) == 0) {
						states[j] = -1;
						break;
					}
				}
				else if ((onNums[a] % 6) == 1 || (onNums[a] % 6) == 5) {
					if ((j & 4) == 0) {
						states[j] = -1;
						break;
					}
				}
				else if ((onNums[a] % 6) == 2 || (onNums[a] % 6) == 4) {
					if ((j & 2) == 0) {
						states[j] = -1;
						break;
					}
				}
				else if ((onNums[a] % 6) == 3) {
					if ((j & 1) == 0) {
						states[j] = -1;
						break;
					}
				}
			}
			for (int b = 0; b < (int)offNums.size(); ++b) { // check if it fits the offNums criteria
				if ((offNums[b] % 6) == 0) {
					if ((j & 8) != 0) {
						states[j] = -1;
						break;
					}
				}
				else if ((offNums[b] % 6) == 1 || (offNums[b] % 6) == 5) {
					if ((j & 4) != 0) {
						states[j] = -1;
						break;
					}
				}
				else if ((offNums[b] % 6) == 2 || (offNums[b] % 6) == 4) {
					if ((j & 2) != 0) {
						states[j] = -1;
						break;
					}
				}
				else if ((offNums[b] % 6) == 3) {
					if ((j & 1) != 0) {
						states[j] = -1;
						break;
					}
				}
			}
		}
	}

	bool impossible = true;
	for (int k = 0; k < (int)states.size(); ++k) {
		if (states[k] > 0) {
			impossible = false;
			for (int pointer = 0; pointer < n; ++pointer) {
				if (pointer % 6 == 0) { // 1 spot
					if ((k & 8) != 0) {
						fout << 1;
					}
					else {
						fout << 0;
					}
				}
				else if (pointer % 6 == 1 || pointer % 6 == 5) { // 2 spot
					if ((k & 4) != 0) {
						fout << 1;
					}
					else {
						fout << 0;
					}
				}
				else if (pointer % 6 == 2 || pointer % 6 == 4) { // 3 spot
					if ((k & 2) != 0) {
						fout << 1;
					}
					else {
						fout << 0;
					}
				}
				else if (pointer % 6 == 3) { // 4 spot
					if ((k & 1) != 0) {
						fout << 1;
					}
					else {
						fout << 0;
					}
				}
				pointer += 1;
			}
			fout << endl;
		}
	}

	if (impossible) {
		fout << "IMPOSSIBLE" << endl;
	}
	return 0;
}