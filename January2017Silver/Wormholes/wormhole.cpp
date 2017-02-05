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

using namespace std;

bool isLoop(const int y1, const int y2) {
	return (y1 == y2);
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

int picktwo(vector<int> &mask, const int level, int &count) {
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
				picktwo(mask, level + 1, count);
				//printMask(mask, level);
				mask[j] = -1;
			}
		}
		mask[i] = -1;
	}
	else {
		for (int j = 0; j < n; ++j) {
			if (j < mask[j]) {
				cout << j << '-' << mask[j] << ' ';
			}
			// cout << mask[j] << ' ';
		}
		cout << endl;
		count += 1;

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

	int z = 6; 
	vector<int> mask(z, -1);
	int count = 0;

	cout << picktwo(mask, 0, count) << endl; 
	
	return 0;
}