#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int danceShow(const int t, vector<int> &dtimes) {
	sort(dtimes.begin(), dtimes.end());
	int n = (int)dtimes.size();
	int k = 0;
	int count = 0;
	vector<int> notused;
	for (int i = 0; i < n; ++i) {
		int best = 0;
		int addj;
		if (dtimes[i] != 0) {
			for (int j = count; j < n; ++j) {
				int add;
				if (i == j) {
					add = dtimes[i];
				}
				else {
					add = dtimes[i] + dtimes[j];
				}

				if (add <= t) {
					if (add > best) {
						best = add;
						addj = j;
					}
				}
				else {
					if (j == n - 1 && best == 0) {
						notused.push_back(dtimes[i]);
					}
				}
			}
			if (best > 0) {
				k += 1;
				dtimes[i] = 0;
				if (k != dtimes[i]) {
					dtimes[addj] = 0;
				}
			}
		}
		count += 1;
	}
	k += (int)notused.size();
	return k;
}

int main() {
	ofstream fout("cowdance.out");
	ifstream fin("cowdance.in");
	int n, t;
	fin >> n >> t;
	vector<int> dtimes(n);
	for (int x = 0; x < n; ++x) {
		int dtime;
		fin >> dtime;
		dtimes[x] = dtime;
	}
	fout << danceShow(t, dtimes) << endl;
	return 0;
}