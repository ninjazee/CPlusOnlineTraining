/*
ID: kml111
PROG: wormhole
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

bool compareTuple(const tuple<int, int> &t1, const tuple<int, int> &t2) {
	if (get<1>(t1) < get<1>(t2)) {
		return true;
	}
	else if (get<1>(t1) == get<1>(t2)) {
		return (get<0>(t1) < get<0>(t2));
	}
	else {
		return false;
	}
}

bool isEnd(const vector<tuple<int, int>> &wormholes, int x) {
	if (x < ((int)wormholes.size() - 1)) {
		if (get<1>(wormholes[x]) < get<1>(wormholes[x + 1])) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}

bool isLoop(const vector<tuple<int, int>> &wormholes, const vector<int> &mask) {
	int n = (int)wormholes.size();


	for (int i = 0; i < n; ++i) {
		int curr = i;
		int loops = 0;
		curr = mask[curr];
		loops += 1;
		while (isEnd(wormholes, curr) == false) {
			curr += 1;
			curr = mask[curr];
			loops += 1;
			if (loops > n) {
				return true;
			}
		}
	}
	return false;
}

void printMask(vector<int> &mask, const int level) {
	for (int i = 0; i < level; i++)
		cout << "........";
	for (int i = 0; i < (int)mask.size(); i++)
		cout << mask[i] << " ";
	cout << endl; 
}


void pickone(vector<int> &mask, const int level) {
	printMask(mask, level); 
	int n = (int)mask.size();
	if (level < n) {
		for (int i = 0; i < n; ++i) {
			if (mask[i] == 0) {
				mask[i] = level + 1;
				pickone(mask, level + 1);
				mask[i] = 0;
			}
		}
	}
	else
	{
		for (int j = 0; j < n; ++j) {
			cout << mask[j] << ' ';
		}
		cout << endl;
	}
}

int picktwo(const vector<tuple<int, int>> &wormholes, vector<int> &mask, const int level, int &count) {
	//printMask(mask, level);
	int n = (int)mask.size();
	if (level < n/2) {
		int i;
		for (i = 0; i < n; ++i) {
			if (mask[i] < 0) {
				mask[i] = level;
				break;
			}
		}
		for (int j = i + 1; j < n; ++j) {
			if (mask[j] < 0) {
				mask[j] = i;
				mask[i] = j;
				/*
				int x = mask[i];
				mask[j] = mask[i];
				mask[i] = x;
				*/
				picktwo(wormholes, mask, level + 1, count);
				//printMask(mask, level);
				mask[j] = -1;
			}
		}
		mask[i] = -1;
	}
	else {
		/*
		for (int j = 0; j < n; ++j) {
			if (j < mask[j]) {
				cout << j << '-' << mask[j] << ' ';
			}
			// cout << mask[j] << ' ';
		}
		cout << endl;
		*/
		
		if (isLoop(wormholes, mask)) {
			count += 1;
		}
		

	}
	return count;
}

int main() {
	ofstream fout("wormhole.out");
	ifstream fin("wormhole.in");
	
	int n;
	fin >> n;
	vector<tuple<int, int>> wormholes(n);
	for (int y = 0; y < n; ++y) {
		int wormholex, wormholey;
		fin >> wormholex >> wormholey;
		wormholes[y] = make_tuple(wormholex, wormholey);
	}

	vector<int> mask(n, -1);
	int count = 0;

	sort(wormholes.begin(), wormholes.end(), compareTuple);

	cout << picktwo(wormholes, mask, 0, count) << endl; 
	
	return 0;
}