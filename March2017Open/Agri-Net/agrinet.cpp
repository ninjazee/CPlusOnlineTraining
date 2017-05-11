/*
ID: kml111
PROG: agrinet
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int minimumSpanningTree(vector<vector<int>> &matrix) {
	int n = (int)matrix.size();
	vector<int> distance(n, numeric_limits<int>::max()); // vector of connections and distance of connections
	vector<bool> intree(n, false); // vector of which nodes are in the tree
	vector<int> source(n, NULL); // vector of the connecting node to this node

	int treesize = 1; // number of nodes in the tree
	int treecost = 0; // total fiber needed
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
		treecost += distance[i]; // increase amount of fiber needed
		intree[i] = true; // mark i as in the tree

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
	ofstream fout("agrinet.out");
	ifstream fin("agrinet.in");
	int n;
	fin >> n;
	vector<vector<int>> matrix(n, vector<int>(n));
	for (int a = 0; a < n; ++a) {
		for (int b = 0; b < n; ++b) {
			int connection;
			fin >> connection;
			matrix[a][b] = connection;
		}
	}

	fout << minimumSpanningTree(matrix) << endl;
	return 0;
}