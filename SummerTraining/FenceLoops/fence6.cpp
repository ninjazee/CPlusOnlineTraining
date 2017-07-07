/*
ID: kml111
PROG: fence6
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_set>

using namespace std;

int main() {
	ofstream fout("fence6.out");
	ifstream fin("fence6.in");
	int n;
	vector<int> segmentLengths(n);
	vector<tuple<vector<int>, vector<int>>> endConnections(n);
	unordered_set<vector<int>> corners;
	for (int a = 0; a < n; ++a) {
		int s, l, n1, n2;
		fin >> s >> l >> n1 >> n2;
		segmentLengths[s - 1] = l;
		vector<int> firstends(n1 + 1);
		firstends[0] = s - 1;
		for (int b = 0; b < n1; ++b) {
			int firstend;
			fin >> firstend;
			get<0>(endConnections[s - 1]).push_back(firstend - 1);
			firstends[b + 1] = firstend - 1;
		}
		vector<int> otherends(n2 + 1);
		otherends[0] = s - 1;
		for (int c = 0; c < n2; ++c) {
			int otherend;
			fin >> otherend;
			get<1>(endConnections[s - 1]).push_back(otherend - 1);
			otherends[c + 1] = otherend - 1;
		}

		if (corners.find(firstends) == corners.end()) {
			corners.insert(firstends);
		}
		if (corners.find(otherends) == corners.end()) {
			corners.insert(otherends);
		}
	}
	return 0;
}