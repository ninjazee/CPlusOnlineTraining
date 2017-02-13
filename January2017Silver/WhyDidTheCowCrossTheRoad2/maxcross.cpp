#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int maxcross(const int k, const vector<int> &signals) {
	int n = (int)signals.size();

	int best = numeric_limits<int>::max();
	for (int i = 0; i < n - k; ++i) {
		if (signals[i] == 0) {
			int brokens = 0;
			for (int j = 0; j < k; ++j) {
				if (signals[i + j] == 1) {
					brokens += 1;
				}
			}
			
			if (brokens < best) {
				best = brokens;
			}
		}
	}
	
	return best;
}

int main() {
	ofstream fout("maxcross.out");
	ifstream fin("maxcross.in");
	int n, k, b;
	fin >> n >> k >> b;
	vector<int> signals(n);
	for (int a = 0; a < b; ++a) {
		int brokenSignal;
		fin >> brokenSignal;
		signals[brokenSignal - 1] = 1;
	}

	fout << maxcross(k, signals) << endl;
	return 0;
}