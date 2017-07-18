/*
ID: kml111
PROG: stall4
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

int bfs(const int start, const int end, vector<unordered_map<int, int>> &adjList, vector<int> &prevNode) {
	int m = (int)prevNode.size();
	vector<int> capacityPath(m);
	capacityPath[start] = numeric_limits<int>::max() / 10;
	queue<int> exam;
	exam.push(start); // add the starting place (the pond) to the queue
	while (!exam.empty()) {
		auto curr = exam.front();
		exam.pop();
		for (auto i : adjList[curr]) { // for all neighbors of current node
			int nextNode = i.first;
			int nextLength = i.second;
			if ((nextLength > 0) && (prevNode[nextNode] == -1)) { // we have not seen this node before and there is available capacity
				prevNode[nextNode] = curr; // change its parent to the current node
				capacityPath[nextNode] = min(capacityPath[curr], nextLength);
				if (nextNode != end) {
					exam.push(nextNode);
				}
				else {
					// we found the stream
					return capacityPath[end];
				}
			}
		}
	}
	return 0;
}

int edmondsKarp(const int start, const int end, vector<unordered_map<int, int>> &adjList) {
	int m = (int)adjList.size();
	int f = 0; // initial max flow is 0
	bool foreverBool = true;
	while (foreverBool) {
		vector<int> prevNode(m, -1);
		prevNode[start] = -2;
		int search = bfs(start, end, adjList, prevNode);
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
	ofstream fout("stall4.out");
	ifstream fin("stall4.in");
	int n, m;
	fin >> n >> m;
	vector<vector<int>> cowStalls(n);
	//vector<vector<int>> stallCows(m);
	for (int a = 0; a < n; ++a) {
		int s;
		fin >> s;
		for (int b = 0; b < s; ++b) {
			int stall;
			fin >> stall;
			cowStalls[a].push_back(stall);
			//stallCows[stall - 1].push_back(a);
		}
	}

	/*
	queue<tuple<int, unordered_set<int>>> exam;
	for (int x = 0; x < cowStalls[0].size(); ++x) {
		unordered_set<int> currLine;
		currLine.insert(cowStalls[0][x]);
		exam.push(make_tuple(0, currLine));
	}

	int best = 0;
	while (!exam.empty()) {
		auto curr = exam.front();
		exam.pop();
		int currCow = get<0>(curr);
		unordered_set<int> currStalls = get<1>(curr);
		int stallAmount = (int)currStalls.size();
		if (stallAmount > best) { // check if we have a larger number of stalls
			best = stallAmount;
		}

		if (currCow < n - 1) { // we have not used all of the cows
			for (int i = 0; i < cowStalls[currCow + 1].size(); ++i) { // for every of the next cow's possible stalls
				if (currStalls.find(cowStalls[currCow + 1][i]) == currStalls.end()) { // if we did not already use this stall
					unordered_set<int> newStalls(currStalls);
					newStalls.insert(cowStalls[currCow + 1][i]);
					exam.push(make_tuple(currCow + 1, newStalls));
				}
			}
		}
	}
	*/

	int numIntersections = m;
	vector<unordered_map<int, int>> adjList(n + m + 2);
	for (int x = 0; x < n; ++x) { // for every cow
		// connect this cow to the "source" node
		// make sure to make capacity 1 because only 1 cow can go to 1 stall
		adjList[0][x + 1] = 1;
		adjList[x + 1][0] = 0;
	}
	for (int y = 0; y < m; ++y) { // for every stall
		// connect this stall to the "sink" node
		// make sure to make capacity 1 because only 1 cow can go to 1 stall
		adjList[y + n + 1][n + m + 1] = 1;
		adjList[n + m + 1][y + n + 1] = 0;
	}
	for (int i = 0; i < n; ++i) { // for every cow
		int numStalls = (int)cowStalls[i].size();
		for (int j = 0; j < numStalls; ++j) { // for every stall this cow can go to
			// link the cow to the stall
			// make sure to make capacity 1 because only 1 cow can go to 1 stall
			adjList[i + 1][cowStalls[i][j] + n] = 1;
			adjList[cowStalls[i][j] + n][i + 1] = 0;
		}
	}

	fout << edmondsKarp(0, n + m + 1, adjList) << endl;
	return 0;
}