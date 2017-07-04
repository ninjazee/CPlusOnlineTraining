/*
ID: kml111
PROG: rockers
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int followGraph(const int m, const int t, const vector<int> &songs, const int discFill, const int numDiscs, const int current, const string &info) {
	int n = (int)songs.size();
	if (current < n) { // we didn't run out of songs
		// skip the current one
		int numUsedSkip = 0;
		numUsedSkip = followGraph(m, t, songs, discFill, numDiscs, current + 1, info);

		// use the current one
		int songTime = songs[current];
		int numUsedUse = 0;
		if ((discFill + songTime) > t) { // if it is too large to fit in the disc
			if (numDiscs < m) { // we haven't used all of the discs
				if (songTime <= t) { // this song actually fits into a disc
					numUsedUse = followGraph(m, t, songs, songTime, numDiscs + 1, current + 1, info + " " + to_string(current) + ":" + to_string(numDiscs + 1)) + 1;
				}
			}
		}
		else {
			numUsedUse = followGraph(m, t, songs, discFill + songTime, numDiscs, current + 1, info + " " + to_string(current) + ":" + to_string(numDiscs)) + 1;
		}

		return max(numUsedSkip, numUsedUse);
	}
	else {
		//cout << info << endl;
		return 0;
	}
}

int main() {
	ofstream fout("rockers.out");
	ifstream fin("rockers.in");
	int n, t, m;
	fin >> n >> t >> m;
	vector<int> songs(n);
	for (int a = 0; a < n; ++a) {
		int song;
		fin >> song;
		songs[a] = song;
	}

	fout << followGraph(m, t, songs, 0, 1, 0, "") << endl;

	return 0;
}