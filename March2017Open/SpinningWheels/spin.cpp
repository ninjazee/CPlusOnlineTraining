/*
ID: kml111
PROG: spin
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

bool spin(const vector<int> &speeds, vector<vector<tuple<int, int>>> &wedgeLocations, const int count) {
	vector<int> current(360);
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < (int)wedgeLocations[i].size(); ++j) {
			int start = get<0>(wedgeLocations[i][j]) + speeds[i] * count;
			int extent = get<1>(wedgeLocations[i][j]);
			for (int c = 0; c <= extent; ++c) {
				current[(start + c) % 360] += 1;
			}
		}
	}
	for (int i = 0; i < 360; ++i) {
		if (current[i] == 5) {
			return true;
		}
	}
	return false;
}

int main() {
	ofstream fout("spin.out");
	ifstream fin("spin.in");
	vector<int> speeds(5);
	vector<vector<tuple<int, int>>> wedgeLocations(5);
	int count = 0;
	for (int a = 0; a < 5; ++a) {
		int speed, w;
		fin >> speed >> w;
		speeds[a] = speed;
		for (int b = 0; b < w; ++b) {
			int start, extent;
			fin >> start >> extent;
			wedgeLocations[a].push_back(make_tuple(start, extent));
		}
	}

	bool foundSpin = false;
	for (int i = 0; i < 360; ++i) {
		if (spin(speeds, wedgeLocations, i)) {
			fout << i << endl;
			foundSpin = true;
			break;
		}
	}
	
	if (!foundSpin) {
		fout << "none" << endl;
	}
	return 0;
}