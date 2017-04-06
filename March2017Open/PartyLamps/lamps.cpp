/*
ID: kml111
PROG: lamps
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void followGraph (string comet) {
	int retValue = 1;
	for (char& c : comet) {
		int diff = c - 'A' + 1;
		retValue *= diff;
	}
	return retValue;
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

	int numTrack = 0;

	return 0;
}