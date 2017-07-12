/*
ID: kml111
PROG: ditch
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int fordFulkerson(const vector<vector<int>> &edgeList, const vector<int> &edgeLengths, vector<int> &prevNode, vector<int> &flow, vector<bool> &visited) {
	int m = (int)prevNode.size();
	bool connected = true;
	while (connected) {
		int maxFlow = 0;
		int maxLoc = -1;
		// find unvisited node with highest capacity
		for (int i = 0; i < m; ++i) {
			if (flow[i] > maxFlow && visited[i] == false) { 
				maxFlow = flow[i];
				maxLoc = i;
			}
		}
		if (maxLoc == -1) {
			// we didn't find any paths, break
			break;
		}
		if (maxLoc = m - 1) {
			// we got to the stream
			break;
		}
		visited[maxLoc] = true;
		// update neighbors of maxLoc

	}
}

int edmondsKarp(const vector<vector<int>> &edgeList, const vector<int> &edgeLengths, vector<int> &prevNode, vector<int> &flow, vector<bool> &visited) {
	int m = (int)prevNode.size();
	bool connected = true;
	while (connected) {
		int maxFlow = 0;
		int maxLoc = -1;
		// find unvisited node with highest capacity
		for (int i = 0; i < m; ++i) {
			if (flow[i] > maxFlow && visited[i] == false) {
				maxFlow = flow[i];
				maxLoc = i;
			}
		}
		if (maxLoc == -1) {
			// we didn't find any paths, break
			break;
		}
		if (maxLoc = m - 1) {
			// we got to the stream
			break;
		}
		visited[maxLoc] = true;
		// update neighbors of maxLoc

	}
}

int main() {
	ofstream fout("ditch.out");
	ifstream fin("ditch.in");
	int n, m;
	fin >> n >> m;
	vector<vector<int>> edgeList(n, vector<int>(2));
	vector<int> edgeLengths(n);
	for (int a = 0; a < n; ++a) {
		int s, e, c;
		fin >> s >> e >> c;
		edgeList[a][0] = s;
		edgeList[a][1] = e;
		edgeLengths[a] = c;
	}

	int totalFlow = 0;
	bool connected = true;
	while (connected) {
		vector<int> prevNode(m, -1);
		vector<int> flow(m, 0);
		vector<bool> visited(m, false);
	}
	return 0;
}