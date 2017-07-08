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
#include <limits>

using namespace std;

void dijkstra(vector<vector<tuple<int, int>>> &adjList, const vector<int> &segmentLengths, const unordered_map<string, int> &corners, const int cornerCount) {
	vector<int> distance(cornerCount, numeric_limits<int>::max() / 10);
	vector<bool> visited(cornerCount, false);
	vector<int> parent(cornerCount, -1);
	for (int i = 0; i < cornerCount; ++i) { // i is the starting node
		int nodesvisited = 0;
		while (nodesvisited < cornerCount) {

		}
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
	vector<vector<string>> cornerEdges(cornerCount);
	for (auto it : corners) {
		cornerEdges[it.second].push_back(it.first);
	}

	vector<vector<int>> edgeList(n, vector<int>(2, -1));
	for (int i = 0; i < cornerCount; ++i) {
		for (string j : cornerEdges[i]) {
			if (edgeList[j[0] - '0'][0] == -1) {
				edgeList[j[0] - '0'][0] = i;
			}
			else {
				if (edgeList[j[0] - '0'][1] == -1) {
					if (edgeList[j[0] - '0'][0] != i) {
						edgeList[j[0] - '0'][1] = i;
					}
				}
			}

			if (edgeList[j[1] - '0'][0] == -1) {
				edgeList[j[1] - '0'][0] = i;
			}
			else {
				if (edgeList[j[1] - '0'][1] == -1) {
					if (edgeList[j[1] - '0'][0] != i) {
						edgeList[j[1] - '0'][1] = i;
					}
				}
			}
		}
	}
	
	vector<vector<tuple<int, int>>> adjList(cornerCount);
	for (int i = 0; i < n; ++i) {
		adjList[edgeList[i][0]].push_back(make_tuple(edgeList[i][1], segmentLengths[i]));
		adjList[edgeList[i][1]].push_back(make_tuple(edgeList[i][0], segmentLengths[i]));
	}
	return 0;
}