#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int maxcross(const int k, vector<int> &brokenSignals, const vector<int> &signals) {
	int b = (int)brokenSignals.size();
	sort(brokenSignals.begin(), brokenSignals.end());
	int n = (int)signals.size();

	vector<int> differences(b - 1);
	for (int i = 0; i < b - 1; ++i) {
		int diff = signals[i + 1] - signals[i];
		differences[i] = diff;
	}

	int best = numeric_limits<int>::max();
	for (int j = 0; j < n; ++j) {
		int total = 0;
		int count = 0;
		while (total < k && count + j < b - 1) {
			total += differences[count + j];
			count += 1;
		}

		if (count - 1 < best) {
			best = count - 1;
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
	vector<int> brokenSignals(b);
	for (int a = 0; a < b; ++a) {
		int brokenSignal;
		fin >> brokenSignal;
		signals[brokenSignal - 1] = 1;
		brokenSignals[a] = brokenSignal;
	}

	cout << maxcross(k, brokenSignals, signals) << endl;
	return 0;
}