#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int minimum(const vector<int> &v) {
	int min = 0;
	for (int x = 0; x < (int)v.size(); ++x) {
		if (v[x] < v[min]) {
			min = x;
		}
	}
	return min;
}

int maximumVal(const vector<int> &v) {
	int max = 0;
	for (int x = 0; x < (int)v.size(); ++x) {
		if (v[x] > max) {
			max = v[x];
		}
	}
	return max;
}

int stageSpots(const int k, const vector<int> &dtimes) {
	vector<int> spots(k, 0);
	for (int a = 0; a < (int)dtimes.size(); ++a) {
		int min = minimum(spots);
		spots[min] += dtimes[a];
	}
	int t = maximumVal(spots);
	return t;
}

int danceShow(const int t, const vector<int> &dtimes) {
	int total = 0;
	for (int i = 0; i < (int)dtimes.size(); ++i) {
		total += dtimes[i];
	}
	int k = 1;
	while (total / k > t) {
		k += 1;
	}
	while (stageSpots(k, dtimes) > t) {
		k += 1;
	}
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