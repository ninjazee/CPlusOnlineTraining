/*
ID: kml111
PROG: race3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool followGraphU(const vector<vector<int>> &adjMatrix, vector<bool> &reached, const int current, const int delNode) { // follow graph for unavoidable points
	if (reached[current]) // if already reached this square it will not lead you anywhere
		return false;
	else if (current == (int)adjMatrix.size() - 1) // we reached the end
		return true;
	else if (current == delNode) // we got to the node that is supposed to be deleted
		return false;
	else {
		reached[current] = true;
		
		bool endReach = false;
		for (int i = 0; i < (int)adjMatrix[current].size(); ++i) {
			if (followGraphU(adjMatrix, reached, adjMatrix[current][i], delNode)) { // we were able to reach the end
				endReach = true;
			}
		}

		return endReach;
	}
}

void followGraphS(const vector<vector<int>> &adjMatrix, vector<int> &reached, const int current, const int course, const int end, bool &commonArrows) { // follow graph for splitting points
	if (reached[current] == course) // if already reached this square in this course it will not lead you anywhere
		int z = 0;
	else if (reached[current] != 0 && reached[current] != course) { // this square has common arrows!
		commonArrows = true;
	}
	else if (current == end) // we reached the end
		int y = 0;
	else {
		reached[current] = course;

		for (int i = 0; i < (int)adjMatrix[current].size(); ++i) {
			followGraphS(adjMatrix, reached, adjMatrix[current][i], course, end, commonArrows);
		}
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
	int n = (int)adjMatrix.size(); // number of points

	// deal with the unavoidable points
	vector<int> unavoidablePoints;
	for (int i = 1; i < n - 1; ++i) { // for every vertex (that's not the start or the end 
		vector<bool> reached(n, false);
		// delete this vertex
		if (!followGraphU(adjMatrix, reached, 0, i)) { // we couldn't reach the end without this point
			unavoidablePoints.push_back(i);
		}
	}
	int unavoidableSize = (int)unavoidablePoints.size();
	fout << unavoidableSize;
	for (int a = 0; a < unavoidableSize; ++a) {
		fout << " " << unavoidablePoints[a];
	}
	fout << endl;

	// deal with the splitting points
	vector<int> splittingPoints;
	for (int i = 0; i < unavoidableSize; ++i) { // for every unavoidable point
		vector<int> splitReached(n, 0);
		bool commonArrows = false;
		followGraphS(adjMatrix, splitReached, 0, 1, unavoidablePoints[i], commonArrows);
		followGraphS(adjMatrix, splitReached, unavoidablePoints[i], 2, n - 1, commonArrows);
		if (!commonArrows) { // there are no common arrows
			splittingPoints.push_back(unavoidablePoints[i]);
		}
	}
	int splittingSize = (int)splittingPoints.size();
	fout << splittingSize;
	for (int b = 0; b < splittingSize; ++b) {
		fout << " " << splittingPoints[b];
	}
	fout << endl;
	return 0;
}