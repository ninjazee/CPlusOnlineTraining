/*
ID: kml111
PROG: milk6
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

#define C_Multiply	1000000000LL
#define C_Add	1000000

long long bfs(const int start, const int end, vector<unordered_map<int, long long>> &adjList, vector<int> &prevNode) {
	int m = (int)prevNode.size();
	vector<long long> capacityPath(m);
	capacityPath[start] = numeric_limits<long long>::max() / 10;
	queue<int> exam;
	exam.push(start); // add the starting place (the productional facility) to the queue
	while (!exam.empty()) {
		auto curr = exam.front();
		exam.pop();
		for (auto i : adjList[curr]) { // for all neighbors of current node
			int nextNode = i.first;
			long long nextLength = i.second;
			if (((nextLength + C_Add * 2) / C_Multiply > 0) && (prevNode[nextNode] == -1)) { // we have not seen this node before and there is available capacity
				prevNode[nextNode] = curr; // change its parent to the current node
				capacityPath[nextNode] = min(capacityPath[curr], nextLength);
				if (nextNode != end) {
					exam.push(nextNode);
				}
				else {
					// we found the warehouse
					return capacityPath[end];
				}
			}
		}
	}
	return 0;
}

long long edmondsKarp(const int start, const int end, vector<unordered_map<int, long long>> &adjList) {
	int m = (int)adjList.size();
	long long f = 0; // initial max flow is 0
	bool foreverBool = true;
	while (foreverBool) {
		vector<int> prevNode(m, -1);
		prevNode[start] = -2;
		long long search = bfs(start, end, adjList, prevNode);
		if (search == 0) {
			foreverBool = false;
			break;
		}
		f += search;
		// backtrack search and write flow;
		int curNode = end;
		while (curNode != start) {
			int lastNode = prevNode[curNode];
			adjList[curNode][lastNode] += search;
			adjList[lastNode][curNode] -= search;
			curNode = lastNode;
		}
	}
	return f;
}

int main() {
	ofstream fout("milk6.out");
	ifstream fin("milk6.in");
	int n, m;
	fin >> n >> m;
	vector<unordered_map<int, long long>> adjList(n);
	vector<vector<int>> adjMatrix(n, vector<int>(n));
	int numWarehouses = n;
	for (int a = 0; a < m; ++a) {
		int s, e;
		long long c;
		fin >> s >> e >> c;
		if (adjList[s - 1].find(e - 1) == adjList[s - 1].end() && adjList[e - 1].find(s - 1) == adjList[e - 1].end()) { // we don't already have an antiparallel edge
			adjList[s - 1][e - 1] = c * C_Multiply - C_Add - a;
			adjList[e - 1][s - 1] = 0;
			adjMatrix[s - 1][e - 1] = a + 1;
		}
		else { // we have an antiparallel edge
			// create a new vertx and reroute the new edge through this vertex.
			unordered_map<int, long long> newVertex;
			newVertex[e - 1] = c * C_Multiply - C_Add - a;
			newVertex[s - 1] = 0;
			adjList.push_back(newVertex);
			adjList[s - 1][numWarehouses] = c * C_Multiply - C_Add - a;
			adjList[e - 1][numWarehouses] = 0;
			numWarehouses += 1;
		}
		
	}


	int maxFlow = edmondsKarp(0, n - 1, adjList);

	// create cut
	vector<bool> black(numWarehouses);
	queue<int> exam;
	exam.push(0);
	while (!exam.empty()) {
		auto curr = exam.front();
		exam.pop();
		black[curr] = true; // mark this node as black

		for (auto i : adjList[curr]) { // for every node we can reach
			// add it to the queue
			int node = i.first;
			if (!black[node]) { // we haven't already seen this node
				if ((i.second + C_Add * 2) / C_Multiply > 0) { // there is some flow
					exam.push(node);
				}
			}
		}
	}

	int cut = 0;
	vector<int> routes;
	for (int i = 0; i < n; ++i) { // for every node (not including extra rerouted nodes)
		if (black[i]) { // if this is a black node
			for (int j = 0; j < n; ++j) { // for every node (not including extra rerouted nodes)
				if (!black[j]) { // if this is not a black node
					auto found = adjList[j].find(i);
					if (found != adjList[j].end() && (found->second + C_Add * 2) / C_Multiply > 0) { // if there is a path here
						// add the cost to the cut
						cut += (found->second + C_Add * 2) / C_Multiply;
						routes.push_back(adjMatrix[i][j]);
					}
				}
			}
		}
	}

	int numRoutes = (int)routes.size();
	cout << cut << " " << numRoutes << endl;
	cout << routes[0];
	for (int x = 1; x < numRoutes; ++x) {
		cout << " " << routes[x];
	}
	cout << endl;
	return 0;
}