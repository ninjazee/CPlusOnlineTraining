/*
ID: kml111
PROG: fence6
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <string>

using namespace std;

void dijkstra(vector<vector<tuple<int, int>>> &adjList, const vector<int> &segmentLengths, const unordered_map<string, int> &corners) {
	int graphsize = (int)corners.size();
	int nodesvisited = 0;
	while (nodesvisited < graphsize) {

	}
}

int main() {
	ofstream fout("fence6.out");
	ifstream fin("fence6.in");
	int n;
	fin >> n;
	vector<int> segmentLengths(n);
	unordered_map<string, int> corners;
	int cornerCount = 0;
	for (int a = 0; a < n; ++a) {
		int s, l, n1, n2;
		fin >> s >> l >> n1 >> n2;
		segmentLengths[s - 1] = l;
		vector<int> firstends(n1 + 1);
		firstends[0] = s - 1;
		for (int b = 0; b < n1; ++b) {
			int firstend;
			fin >> firstend;
			firstends[b + 1] = firstend - 1;
		}
		bool foundNewCornerF = false;
		for (int x = 0; x <= n1; ++x) {
			for (int y = 0; y <= n1; ++y) {
				if (x != y) {
					int num1, num2;
					if (firstends[x] <= firstends[y]) {
						num1 = firstends[x];
						num2 = firstends[y];
					}
					else {
						num1 = firstends[y];
						num2 = firstends[x];
					}
					string firstendstr = to_string(num1) + to_string(num2);
					if (corners.find(firstendstr) == corners.end()) {
						corners[firstendstr] = cornerCount;
						foundNewCornerF = true;
					}
				}
			}
		}
		if (foundNewCornerF) {
			cornerCount += 1;
		}

		vector<int> otherends(n2 + 1);
		otherends[0] = s - 1;
		for (int c = 0; c < n2; ++c) {
			int otherend;
			fin >> otherend;
			otherends[c + 1] = otherend - 1;
		}
		bool foundNewCornerO = false;
		for (int x = 0; x <= n2; ++x) {
			for (int y = 0; y <= n2; ++y) {
				if (x != y) {
					int num1, num2;
					if (otherends[x] <= otherends[y]) {
						num1 = otherends[x];
						num2 = otherends[y];
					}
					else {
						num1 = otherends[y];
						num2 = otherends[x];
					}
					string otherendstr = to_string(num1) + to_string(num2);
					if (corners.find(otherendstr) == corners.end()) {
						corners[otherendstr] = cornerCount;
						foundNewCornerO = true;
					}
				}
			}
		}
		if (foundNewCornerO) {
			cornerCount += 1;
		}
	}

	int graphsize = (int)corners.size();
	vector<vector<string>> cornerEdges(graphsize);
	for (auto it : corners) {
		cornerEdges[it.second].push_back(it.first);
	}
	
	vector<vector<tuple<int, int>>> adjList(graphsize);
	for (int i = 0; i < graphsize; ++i) {
		for (int j = 0; j < graphsize; ++j) {
			if (i != j) {

			}
		}
	}
	return 0;
}