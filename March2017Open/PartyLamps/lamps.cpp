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
	states[0] = 1;
	for (int i = 0; i < c; ++i) {
		pressButton(states);
		cout << "Press " << i + 1 << endl;
		for (int j = 0; j < (int)states.size(); ++j) {
			cout << bitset<4>(j) << ": " << states[j] << endl;
		}
		cout << endl;
	}

	/*
	for (int j = 0; j < (int)states.size(); ++j) {
		if (states[j] != 0) { // some lamps are in this state
			for (int a = 0; a < (int)onNums.size(); ++a) {

			}
		}
	}
	*/
	return 0;
}