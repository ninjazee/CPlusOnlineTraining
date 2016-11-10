/*
ID: kml111
PROG: milk2
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>

using namespace std;

struct MyCompare
{
	bool operator()(const tuple<int,int> &t1, const tuple<int,int> &t2)
	{
		return ( (get<0>(t1) < get<0>(t2))||(get<0>(t1)==get<0>(t2) && get<1>(t1) > get<1>(t2)) );
	}
};


void longestTimes(int n, vector<tuple<int, int>> &times, vector<int> &numCowsTime, int &cowsBest, int &noCowsBest) {
	// sort out the vectors
	sort(times.begin(), times.end(), MyCompare());
	int count = 0;
	for (int j = 0; j < (2 * n); ++j) {
		tuple<int, int> time = times[j];
		count += get<1>(time);
		numCowsTime[j] = count;
	}
	
	// check at what point no cows are being milked
	noCowsBest = 0;
	for (int k = 0; k < (2 * n) - 1; ++k) {
		if (numCowsTime[k] == 0) {
			tuple<int, int> stime = times[k];
			tuple<int, int> ftime = times[k + 1];
			int length = get<0>(ftime) - get<0>(stime);
			if (length > noCowsBest) {
				noCowsBest = length;
			}
		}
	}

	// check how long at least one cow is being milked
	cowsBest = 0;
	int lengthMilking = 0;
	int startTime = get<0>(times[0]);
	for (int m = 1; m < (2 * n); ++m) {
		lengthMilking = get<0>(times[m]) - startTime;
		if (numCowsTime[m] == 0) {
			if (lengthMilking > cowsBest) {
				cowsBest = lengthMilking;
			}
			lengthMilking = 0;
			if (m < (2 * n) - 1) {
				startTime = get<0>(times[m + 1]);
			}
		}
	}

}


int main() {
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");
	int n;
	fin >> n;
	vector<tuple<int, int>> times(2 * n);
	int placehold = 0;
	for (int i = 0; i < n; ++i) {
		int s, f;
		fin >> s >> f;
		auto start = make_tuple(s, 1);
		auto finish = make_tuple(f, -1);
		times[placehold] = start;
		times[placehold + 1] = finish;
		placehold += 2;
	}
	vector<int> numCowsTime(2 * n);
	int cowsBest = 0;
	int noCowsBest = 0;
	longestTimes(n, times, numCowsTime, cowsBest, noCowsBest);
	fout << cowsBest << " " << noCowsBest << endl;
	return 0;
}