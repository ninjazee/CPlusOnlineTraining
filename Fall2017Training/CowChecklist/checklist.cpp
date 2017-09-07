/*
ID: kml111
PROG: checklist
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

int findDist(const tuple<int, int> t1, const tuple<int, int> t2) {
	// calculate distance between two nodes
	int xDist = abs(get<0>(t1) - get<0>(t2));
	int yDist = abs(get<1>(t1) - get<1>(t2));
	int dist = (xDist * xDist) + (yDist * yDist);
	return dist;
}

int main() {
	ofstream fout("checklist.out");
	ifstream fin("checklist.in");
	int h, g;
	fin >> h >> g;
	vector<tuple<int, int>> holsteins(h);
	vector<tuple<int, int>> guernseys(g);
	for (int a = 0; a < h; ++a) {
		int x, y;
		fin >> x >> y;
		holsteins[a] = make_tuple(x, y);
	}
	for (int b = 0; b < g; ++b) {
		int x, y;
		fin >> x >> y;
		guernseys[b] = make_tuple(x, y);
	}

	// start dynamic programming
	vector<vector<int>> combinations(h + 1, vector<int>(g + 1, 0));
	for (int c = 2; c <= h; ++c) { // only holsteins
		combinations[c][0] = findDist(holsteins[c - 2], holsteins[c - 1]) + combinations[c - 1][0];
	}
	for (int d = 2; d <= g; ++d) { // only guernseys
		combinations[0][d] = findDist(guernseys[d - 2], guernseys[d - 1]) + combinations[0][d - 1];
	}

	for (int i = 1; i <= h; ++i) { // for every number of holsteins
		for (int j = 1; j <= g; ++j) { // for every number of guernseys
			int hVal = numeric_limits<int>::max();
			int gVal = numeric_limits<int>::max();
			int currDist = findDist(holsteins[i - 1], guernseys[j - 1]);
			if (i - 2 >= 0) { // there are two exsisting holsteins
				if (j == 1) {
					gVal = combinations[1][1];
				}
				else {
					gVal = combinations[i][j - 1];
				}
			}
			if (j - 2 >= 0) { // there are two exsisting guernseys
				/*
				int gDist = findDist(guernseys[j - 2], guernseys[j - 1]);
				if (i == 1) {
					gDist = max(gDist, findDist(holsteins[j - 1], guernseys[0]));
				}
				hVal = min(gDist, combinations[i - 1][j]);
				*/
				if (j == 1) {
					hVal = combinations[1][1];
				}
				else {
					hVal = combinations[i - 1][j];
				}
			}
			

			int moreHolsteinVals = combinations[i][j - 1] + min(hVal, currDist);
			int moreGuernseyVals = combinations[i - 1][j] + min(gVal, currDist);
			combinations[i][j] = min(moreHolsteinVals, moreGuernseyVals);
		}
	}

	cout << combinations[h][g] << endl;
	return 0;
}