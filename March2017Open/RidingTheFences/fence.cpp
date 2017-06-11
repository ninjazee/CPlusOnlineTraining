/*
ID: kml111
PROG: fence
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

#define MAXNODES 501

void find_circuit(vector<map<int, int>> &graph, vector<int> &circuit, const int currentNode) {
	while (!graph[currentNode].empty()) { // has neighbors
		auto pnt = graph[currentNode].begin();
		int j = pnt->first;
		pnt->second--;
		auto pnt1 = graph[j].find(currentNode);
		pnt1->second--;
		if (pnt->second == 0) {
			graph[currentNode].erase(pnt);
			graph[j].erase(pnt1);
		}
		find_circuit(graph, circuit, j);
	}
	circuit.push_back(currentNode);
}

int main() {
	ofstream fout("fence.out");
	ifstream fin("fence.in");
	int f;
	fin >> f;
	vector<map<int,int>> graph(MAXNODES, map<int,int>());
	int smallest = MAXNODES;
	for (int a = 0; a < f; ++a) {
		int i, j;
		fin >> i >> j;
		auto it = graph[i].find(j);
		if (it == graph[i].end()) { // not already in
			graph[i].insert(make_pair(j, 1));
			graph[j].insert(make_pair(i, 1));
		}
		else {
			it->second++; 
			auto it2 = graph[j].find(i);
			it2->second++;
		}
		if (i < smallest) {
			smallest = i;
		}
		if (j < smallest) {
			smallest = j;
		}
	}
	vector<int> circuit;
	smallest += MAXNODES; 
	for (int b = 0; b < MAXNODES; ++b) {
		int numEdges = 0; 
		for (auto it : graph[b])
			numEdges += it.second;
		if ( numEdges % 2 != 0) {
			smallest = min(smallest, b);
		}
	}
	smallest %= MAXNODES;

	find_circuit(graph, circuit, smallest);

	for (int i = (int)circuit.size() - 1; i >= 0; --i) {
		fout << circuit[i] << endl;
	}
	return 0;
}