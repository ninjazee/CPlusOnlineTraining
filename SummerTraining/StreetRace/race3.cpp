/*
ID: kml111
PROG: race3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool followGraph(const vector<vector<int>> &adjMatrix, vector<int> reached, const int current, const int course) {
	if (reached[current] != 0) // if already reached this square it will not lead you anywhere
		return false;
	else if (current == (int)adjMatrix.size()) // we reached the end
		return true;
	else {
		reached[current] = course;
		
		int endReach = false;
		for (int i = 0; i < (int)adjMatrix[current].size(); ++i) {
			if (followGraph(adjMatrix, reached, adjMatrix[current][i], course)) { // we were able to reach the end
				endReach = true;
			}
		}

		return endReach;
	}
}

int main() {
	ofstream fout("race3.out");
	ifstream fin("race3.in");
	vector<vector<int>> adjMatrix;
	int vertex = 0;
	int x = 0;
	while (x != -1) {
		fin >> x;
		if (x != -2) {
			adjMatrix.push_back(vector<int>());
		}
		while (x != -2 && x != -1) {
			adjMatrix[vertex].push_back(x);
			fin >> x;
		}
		vertex += 1;
	}
	int n = vertex;

	for (int i = 0; i < n; ++i) { // for every vertex
		vector<vector<int>> tempMatrix(adjMatrix);
		// delete this vertex
		for (int j = 0; j < (int)adjMatrix[i].size(); ++j) {
			tempMatrix[i].erase(j);
			
		}
	}
	return 0;
}