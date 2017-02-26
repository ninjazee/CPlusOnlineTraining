/*
ID: kml111
PROG: numtri
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void findPaths(const vector<vector<int>> &tree, int &total, const int level, const int pos, int &best) {
	int r = (int)tree.size();
	if (level < r - 1) { // if not at bottom
		for (int i = 0; i < 2; ++i) { // for each of the two children nodes
			total += tree[level + 1][pos + i]; // increase the total so far by the value of the child
			findPaths(tree, total, level + 1, pos + i, best); // depth first search
			total -= tree[level + 1][pos + i]; // reset total
		}
	}
	else {
		if (total > best) { // is it the new maximum?
			best = total;
		}
		//cout << total + tree[0][0] << ' ' << pos << endl;
	}
}

void findPaths2(const vector<vector<int>> &tree, int &total, const int level, const int pos, vector<int> &totals) {
	int r = (int)tree.size();
	totals.push_back(total);
	if (level < r - 1) { // if not at bottom
		for (int i = 0; i < 2; ++i) { // for each of the two children nodes
			total += tree[level + 1][pos + i]; // increase the total so far by the value of the child
			findPaths2(tree, total, level + 1, pos + i, totals); // depth first search
			total -= tree[level + 1][pos + i]; // reset total
		}
	}
}

void findPaths3(const vector<vector<int>> &tree, vector<vector<int>> &totals) {
	int r = (int)tree.size();
	for (int i = 0; i < r - 1; ++i) { // go through each row except the last
		for (int j = 0; j < i + 1; ++j) { // go through each value
			for (int k = 0; k < 2; ++k) { // go through both children
				if (totals[i + 1][j + k] < totals[i][j] + tree[i + 1][j + k]) { // check to make sure the biggest possible node is put in
					totals[i + 1][j + k] = totals[i][j] + tree[i + 1][j + k];
				}
			}
		}
	}
}

int main() {
	ofstream fout("numtri.out");
	ifstream fin("numtri.in");
	int r;
	fin >> r; // get number of rows
	
	vector<vector<int>> tree(r); // create a vector with rows of vectors for the tree
	for (int x = 0; x < r; ++x) { // for each row
		tree[x] = vector<int>(x + 1);
		for (int y = 0; y <= x; ++y) { // for each element in the row
			int a;
			fin >> a;
			tree[x][y] = a;
		}
	}

	int best = 0;
	int total = tree[0][0];
	vector<vector<int>> totals(r);
	for (int z = 0; z < r; ++z) {
		totals[z] = vector<int>(z + 1, 0);
	}
	totals[0][0] = tree[0][0];
	findPaths3(tree, totals);

	sort(totals[r - 1].begin(), totals[r - 1].end()); // sort vector of sums
	fout << totals[r - 1][(int)totals[r - 1].size() - 1] << endl; // return largest sum
	return 0;
}