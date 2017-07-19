/*
ID: kml111
PROG: job
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int convert(string comet) {
	int retValue = 1;
	for (char& c : comet) {
		int diff = c - 'A' + 1;
		retValue *= diff;
	}
	return retValue;
}

int main() {
	ofstream fout("job.out");
	ifstream fin("job.in");
	int n, m1, m2;
	fin >> n >> m1 >> m2;
	vector<int> aMachines(m1);
	for (int x = 0; x < m1; ++x) {
		int a;
		fin >> a;
		aMachines[x] = a;
	}
	vector<int> bMachines(m2);
	for (int y = 0; y < m2; ++y) {
		int b;
		fin >> b;
		bMachines[y] = b;
	}

	multimap<int, int> endTimes; // a map of which one finishes fastest
	for (int i = 0; i < m1; ++i) { // for every A machine
		// insert
		endTimes.insert(make_pair(aMachines[i], 0)); // end, start
	}

	int time = 0;
	vector<tuple<int, int>> aJobs(n);
	for (int i = 0; i < n; ++i) { // for every job
		// assign it to the job that finishes first
		auto curr = endTimes.begin();
		int currend = curr->first;
		int currstart = curr->second;
		int jobLength = currend - currstart;
		endTimes.erase(curr);
		aJobs[i] = make_tuple(currstart, currend);
		endTimes.insert(make_pair(currend + jobLength, currstart + jobLength));
		time = currstart + jobLength;
	}

	cout << time << endl;
	return 0;
}