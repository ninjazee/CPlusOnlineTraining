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
#include <map>

using namespace std;

int dijkstra(const vector<unordered_map<int, int>> &adjList, vector<int> &distance, vector<bool> &visited, vector<int> &parent, const int start, const int end) {
	int cornerCount = (int)adjList.size();
	distance[start] = 0;
	multimap<int, int> reachable;
	reachable.insert(make_pair(0, start));
	while (!reachable.empty()) { // while there are still places to reach
		auto curr = reachable.begin();
		int currDist = curr->first;
		int currNode = curr->second;
		reachable.erase(curr);
		if (currNode == end) { // we found the end node
			return currDist;
		}
		if (!visited[currNode]) {
			visited[currNode] = true;
			for (auto it : adjList[currNode]) {
				if (it.second + currDist < distance[it.first]) {
					distance[it.first] = it.second + currDist;
					parent[it.first] = currNode;
					reachable.insert(make_pair(it.second + currDist, it.first));
				}
			} 
		}
	}
	return numeric_limits<int>::max() / 10;
}

int findShortestLoops( vector<unordered_map<int, int>> &adjList, const vector<vector<int>> &edgeList) {
	int cornerCount = (int)adjList.size();
	int best = numeric_limits<int>::max() / 10;
	for (int i = 0; i < (int)edgeList.size(); ++i) { // for every edge
		// erase it from the adjacency list
		int p1 = edgeList[i][0];
		int p2 = edgeList[i][1];
		auto it = adjList[p1].find(p2);
		int edgeLength = it->second;
		adjList[p1].erase(p2);
		adjList[p2].erase(p1);

		vector<int> distance(cornerCount, numeric_limits<int>::max() / 10);
		vector<bool> visited(cornerCount, false);
		vector<int> parent(cornerCount, -1);
		int loopDist = dijkstra(adjList, distance, visited, parent, p1, p2);
		if (loopDist + edgeLength < best) {
			best = loopDist + edgeLength;
		}
		adjList[p1][p2] = edgeLength;
		adjList[p2][p1] = edgeLength;
	}
	return best;
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
					string otherendstr = string(1,'0'+num1) + string(1,'0'+num2);
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
	
	vector<unordered_map<int, int>> adjList(cornerCount);
	for (int i = 0; i < n; ++i) {
		adjList[edgeList[i][0]][edgeList[i][1]] = segmentLengths[i];
		adjList[edgeList[i][1]][edgeList[i][0]] = segmentLengths[i];
	}

	int retVal = findShortestLoops(adjList, edgeList);
	cout << retVal << endl;
	return 0;
}