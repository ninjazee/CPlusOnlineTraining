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
	
	// a machines
	multimap<int, int> aEndTimes; // a map of which one finishes fastest
	for (int i = 0; i < m1; ++i) { // for every A machine
		// insert
		aEndTimes.insert(make_pair(aMachines[i], 0)); // end, start
	}
	int aTime = 0;
	vector<tuple<int, int>> aJobs(n);
	for (int i = 0; i < n; ++i) { // for every job
		// assign it to the machine that finishes first
		auto curr = aEndTimes.begin();
		int currend = curr->first;
		int currstart = curr->second;
		int jobLength = currend - currstart;
		aEndTimes.erase(curr);
		aJobs[i] = make_tuple(currstart, currend);
		aEndTimes.insert(make_pair(currend + jobLength, currstart + jobLength));
		aTime = currstart + jobLength;
	}

	// b machines
	multimap<tuple<int, int>, int> bEndTimes; // a map of which one finishes fastest
	for (int i = 0; i < m2; ++i) { // for every B machine
		// insert
		bEndTimes.insert(make_pair(make_tuple(bMachines[i], 0), i)); // end, start, machine #
	}
	int bTime = 0;
	vector<tuple<int, int, int>> bJobs(n);
	for (int i = 0; i < n; ++i) { // for every job
		// assign it to the machine that finishes first
		auto curr = bEndTimes.begin();
		int currend = get<0>(curr->first);
		int currstart = get<1>(curr->first);
		int jobLength = currend - currstart;
		int machNum = curr->second;
		bEndTimes.erase(curr);
		bJobs[i] = make_tuple(currstart, currend, machNum);
		bEndTimes.insert(make_pair(make_tuple(currend + jobLength, currstart + jobLength), machNum));
		bTime = currstart + jobLength;
	}

	int maxTotalTime = 0;
	vector<int> bCoolDown(m2, 0);
	for (int i = 0; i < n; ++i) { // for every job
		// add the corresponding aJob and bJob on the opposite end of the spectrum
		int currTotal = get<1>(aJobs[i]) + (get<1>(bJobs[n - i - 1]) - get<0>(bJobs[n - i - 1]));
		if (bCoolDown[get<2>(bJobs[n - i - 1])] > get<1>(aJobs[i])) { // there is still some time before the machine finishes its last job
			currTotal += bCoolDown[get<2>(bJobs[n - i - 1])] - get<1>(aJobs[i]); // add that time
		}
		bCoolDown[get<2>(bJobs[n - i - 1])] = currTotal;
		if (currTotal > maxTotalTime) {
			maxTotalTime = currTotal;
		}
	} 

	fout << aTime << ' ' << maxTotalTime << endl;
	return 0;
}