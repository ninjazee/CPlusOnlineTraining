/*
ID: kml111
PROG: milk3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct HashVector {
	size_t operator() (vector<int> const& vec) const {
		size_t seed = vec.size();
		for (auto& i : vec) {
			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}

};

void milk3(const vector<int> &capacity, vector<int> &current, unordered_set<vector<int>, HashVector> &tree) {
	auto got = tree.find(current);
	if (got == tree.end()) {
		/*
		for (int z : current) {
			cout << z << ' ';
		}
		cout << endl;
		*/
		tree.insert(current);
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				vector<int> newBucket(current);
				int pouring = min(current[i], capacity[j] - current[j]);
				newBucket[j] += pouring;
				newBucket[i] -= pouring;
				/*
				if (current[i] > capacity[j] - current[j]) {
					newBucket[i] = 0;
					newBucket[j] += current[i];
				}
				else {
					newBucket[j] = capacity[j];
					newBucket[i] -= capacity[j] - current[j];
				}
				*/
				milk3(capacity, newBucket, tree);
			}
		}
	}
}

int main() {
	ofstream fout("milk3.out");
	ifstream fin("milk3.in");
	int A, B, C;
	fin >> A >> B >> C;
	unordered_set<vector<int>, HashVector> tree;
	int startArray[3] = { 0, 0, C };
	vector<int> start(startArray, startArray + sizeof(startArray) / sizeof(int));

	int capacityArray[3] = { A, B, C };
	vector<int> capacity(capacityArray, capacityArray + sizeof(capacityArray) / sizeof(int));

	vector<int> retVector;

	milk3(capacity, start, tree);
	for (vector<int> x : tree) {
		if (x[0] == 0) {
			retVector.push_back(x[2]);
		}
	}
	sort(retVector.begin(), retVector.end());

	for (int y = 0; y < (int)retVector.size(); ++y) {
		if (y == (int)retVector.size() - 1) {
			fout << retVector[y];
		}
		else {
			fout << retVector[y] << ' ';
		}
	}
	fout << endl;
	return 0;
}