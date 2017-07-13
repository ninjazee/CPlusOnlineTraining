/*
ID: kml111
PROG: ditch
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

/*
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
*/

int bfs(const vector<unordered_map<int, int>> &adjList, vector<int> &prevNode, vector<bool> &visited, vector<vector<int>> &flow) {
	int m = (int)prevNode.size();
	vector<int> capacityPath(m);
	capacityPath[0] = numeric_limits<int>::max() / 10;
	queue<int> exam;
	exam.push(0); // add the starting place (the pond) to the queue
	while (!exam.empty()) {
		auto curr = exam.front();
		exam.pop();
		for (auto i : adjList[curr]) { // for all neighbors of current node
			int nextNode = i.first;
			int nextLength = i.second;
			if ((nextLength + flow[curr][nextNode] > 0) && (prevNode[nextNode] = -1)) { // we have not seen this node before and there is available capacity
				prevNode[nextNode] = curr;
				capacityPath[nextNode] = min(capacityPath[curr], nextLength - flow[curr][nextNode]);
				if (nextNode != m - 1) {
					exam.push(nextNode);
				}
				else {
					return capacityPath[m - 1];
				}
			}
		}
	}
	return 0;
}

int edmondsKarp(const vector<unordered_map<int, int>> &adjList, vector<vector<int>> &flow) {
	int m = (int)flow.size();
	int f = 0;
	bool foreverBool = true;
	while (foreverBool) {
		vector<int> prevNode(m, -1);
		vector<bool> visited(m, false);
		int search = bfs(adjList, prevNode, visited, flow);
		if (search == 0) {
			foreverBool = false;
			break;
		}
		f += search;
		// backtrack search and write flow;
		int curNode = m - 1;
		while (curNode != 0) {
			int lastNode = prevNode[curNode];
			flow[curNode][lastNode] += search;
			flow[lastNode][curNode] -= search;
			curNode = lastNode;
		}
	}
	return f;
}

int main() {
	ofstream fout("ditch.out");
	ifstream fin("ditch.in");
	int n, m;
	fin >> n >> m;
	vector<vector<int>> edgeList(n, vector<int>(2));
	vector<int> edgeCapacities(n);
	for (int a = 0; a < n; ++a) {
		int s, e, c;
		fin >> s >> e >> c;
		edgeList[a][0] = s - 1;
		edgeList[a][1] = e - 1;
		edgeCapacities[a] = c;
	}

	vector<unordered_map<int, int>> adjList(m);
	for (int i = 0; i < n; ++i) {
		adjList[edgeList[i][0]][edgeList[i][1]] = edgeCapacities[i];
	}

	vector<vector<int>> flow(m, vector<int>(m));
	fout << edmondsKarp(adjList, flow) << endl;
	return 0;
}