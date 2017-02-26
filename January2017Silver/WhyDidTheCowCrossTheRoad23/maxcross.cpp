#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int maxcross(const int k, const vector<int> &signals) {
	int n = (int)signals.size();

	int best = numeric_limits<int>::max();
	int brokens = 0;
	for (int j = 0; j < k; ++j) {
		if (signals[j] == 1) {
			brokens += 1;
		}
	}
	for (int i = 1; i < n - k + 1; ++i) {
		if (signals[i - 1] == 1) {
			brokens -= 1;
		}

		if (signals[i + k - 1] == 1) {
			brokens += 1;
		}

		if (brokens < best) {
			best = brokens;
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