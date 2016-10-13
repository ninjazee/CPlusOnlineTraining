#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


int circularBarn(int n, const vector<int> &rooms) {
	int cNum = 0;
	for (int i = 0; i < n; ++i) {
		cNum += rooms[i];
	}

	int least = numeric_limits<int>::max();

	for (int k = 0; k < n; ++k) {
		int count = 0;
		int c = 0;
		while (c < n) {
			// Step: # of steps walked by cow in room c
			int step = (c - k + n) % n;
			count += rooms[c] * step;
			c += 1;
		}
		
		if (count < least) {
			least = count;
		}
	}

	return least;
}

int main() {
	ofstream fout("cbarn.out");
	ifstream fin("cbarn.in");
	int n;
	fin >> n;
	vector<int> rooms(n);
	for (int j = 0; j < n; ++j) {
		int r;
		fin >> r;
		rooms[j] = r;
	}
	cout << circularBarn(n, rooms) << endl;
	return 0;
}