/*
ID: kml111
PROG: moocast
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <limits>
#include <cmath>

using namespace std;

int minimumSpanningTree(vector<vector<int>> &matrix, vector<int> &treeLengths) {
	int n = (int)matrix.size();
	vector<int> distance(n, numeric_limits<int>::max()); // vector of connections and distance of connections
	vector<bool> intree(n, false); // vector of which nodes are in the tree
	vector<int> source(n, NULL); // vector of the connecting node to this node

	int treesize = 1; // number of nodes in the tree
	int treecost = 0; // total money needed
	intree[0] = true; // start with the first node
	for (int j = 0; j < n; ++j) { // for all of the neighbors of the first node
		distance[j] = matrix[0][j]; // update the distances
		source[j] = 0; // mark that this node connects to the first node
	}

	while (treesize < n) {
		// find node with minimum distance to tree; call it node i'
		int smallestDist = numeric_limits<int>::max();
		int i = 0;
		for (int d = 0; d < n; ++d) {
			if (distance[d] < smallestDist && intree[d] == false) {
				smallestDist = distance[d];
				i = d;
			}
		}

		// add edge source[i], i to minimum spanning tree
		treesize += 1; // increase size of tree by 1
		treecost += distance[i]; // increase amount of money needed
		intree[i] = true; // mark i as in the tree
		treeLengths.push_back(distance[i]);

		// update distance of other nodes after node i added
		for (int j = 0; j < n; ++j) {
			if (distance[j] > matrix[i][j]) {
				distance[j] = matrix[i][j];
				source[j] = i;
			}
		}
	}

	return treecost;
}

int main() {
	ofstream fout("moocast.out");
	ifstream fin("moocast.in");
	int n;
	fin >> n;
	vector<tuple<int, int>> cowCoords(n);
	for (int a = 0; a < n; ++a) {
		int x, y;
		fin >> x >> y;
		cowCoords[a] = make_tuple(x, y);
	}

	vector<vector<int>> adjMatrix(n, vector<int>(n));
	for (int i = 0; i < n; ++i) { // for every node
		for (int j = i + 1; j < n; ++j) { // for another node
			// calculate distance between the two nodes
			int xDist = abs(get<0>(cowCoords[i]) - get<0>(cowCoords[j]));
			int yDist = abs(get<1>(cowCoords[i]) - get<1>(cowCoords[j]));
			int dist = (xDist * xDist) + (yDist * yDist);
			// put that value as the adjMatrix value
			adjMatrix[i][j] = dist;
			adjMatrix[j][i] = dist;
		}
	}

	vector<int> treeLengths; // vector of connections and distance of connections
	int cost = minimumSpanningTree(adjMatrix, treeLengths);

	int largestCost = 0;
	for (int i = 0; i < (int)treeLengths.size(); ++i) {
		if (treeLengths[i] > largestCost) {
			largestCost = treeLengths[i];
		}
	}

	fout << largestCost << endl;
	return 0;
}